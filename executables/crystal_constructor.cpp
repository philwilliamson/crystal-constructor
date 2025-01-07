#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <crystal_constructor/opengl_graphics/mesh.h>
#include <crystal_constructor/crystal_model/crystal_model.h>
#include <crystal_constructor/crystal_model/graphics_crystal_model_view.h>
#include <crystal_constructor/utils/gen_sphere_mesh_data.h>
#include <crystal_constructor/user_interface/gui_handler.h>

const unsigned int width = 1280;
const unsigned int height = 720;

namespace {
float currentAspect{(float)width / (float)height};
float lastFrame{0.0f};
} // working variables for graphics loop

void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight)
{
    currentAspect = (float)newWidth / (float)newHeight;
    glViewport(0, 0, newWidth, newHeight);
}  

int main() {
    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Crystal Constructor", NULL, NULL);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 

    // Check for Valid Context
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    gladLoadGL();
    glViewport(0, 0, width, height);

    crystal_constructor::crystal_model::CrystalModel crystalModel{};
    crystal_constructor::crystal_model::GraphicsCrystalModelView graphicsCrystalModelView{crystalModel};

    crystal_constructor::opengl_graphics::MeshData initialCellMeshData{graphicsCrystalModelView.GetCellMeshData()};
    crystal_constructor::opengl_graphics::Mesh crystalCellMesh{initialCellMeshData.vertices, initialCellMeshData.indices};

    crystal_constructor::opengl_graphics::MeshData sphereMeshData{crystal_constructor::utils::gen_sphere_mesh_data(0.1f,50,50)};
    crystal_constructor::opengl_graphics::Mesh atomMesh{sphereMeshData.vertices, sphereMeshData.indices};

    crystal_constructor::user_interface::GUIHandler guiHandler{crystalModel, window};
    crystal_constructor::opengl_graphics::Camera camera{currentAspect};
    crystal_constructor::opengl_graphics::Shader crystalCellShader{"shaders/crystal_cell_lines.vert", "shaders/crystal_cell_lines.frag"};
    crystal_constructor::opengl_graphics::Shader atomShader{"shaders/atom.vert", "shaders/atom.frag"};

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    
    // // Rendering Loop
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera.SetAspect(currentAspect);
        if (!guiHandler.GUICapturedMouse())
        {
            camera.UpdateFromInputs(window, deltaTime);
        }

        crystal_constructor::user_interface::InputBasis inputBasis{guiHandler.GetInputBasis()};
        crystalModel.SetAHat(crystal_constructor::crystal_model::Vector3{
            inputBasis.guiAHat[0], inputBasis.guiAHat[1], inputBasis.guiAHat[2]
        });
        crystalModel.SetBHat(crystal_constructor::crystal_model::Vector3{
            inputBasis.guiBHat[0], inputBasis.guiBHat[1], inputBasis.guiBHat[2]
        });
        crystalModel.SetCHat(crystal_constructor::crystal_model::Vector3{
            inputBasis.guiCHat[0], inputBasis.guiCHat[1], inputBasis.guiCHat[2]
        });

        std::optional<crystal_constructor::crystal_model::Atom> newAtom{guiHandler.GetAndResetAddOnAtomParams()};
        if (newAtom.has_value())
        {
            crystalModel.AddOnAtom(newAtom.value());
        }

        std::optional<int> removeAtomIdx{guiHandler.GetAndResetRemoveAtomIdx()};
        if (removeAtomIdx.has_value())
        {
            crystalModel.RemoveAtom(removeAtomIdx.value());
        }
        
        crystal_constructor::opengl_graphics::MeshData updatedCellMeshData{graphicsCrystalModelView.GetCellMeshData()};
        crystalCellMesh.SetVertices(updatedCellMeshData.vertices);
        crystalCellMesh.SetModelMatrix(graphicsCrystalModelView.GetModelMatrix());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        crystalCellMesh.Draw(crystalCellShader, camera, GL_LINES);

        const std::vector<crystal_constructor::crystal_model::AtomDrawData> modelAtomsDrawData{graphicsCrystalModelView.GetAtomsUniformData()};

        for (int idx = 0; idx < modelAtomsDrawData.size(); idx++)
        {
            crystal_constructor::crystal_model::AtomDrawData currentAtomDrawData{modelAtomsDrawData.at(idx)};

            atomShader.UpdateUniform3fv("atomColor", currentAtomDrawData.color);
            atomMesh.SetModelMatrix(currentAtomDrawData.modelMatrix);

            atomMesh.Draw(atomShader, camera);
        }
        
        guiHandler.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    guiHandler.Shutdown();

    crystalCellShader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
