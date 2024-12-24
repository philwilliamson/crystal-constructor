#include <iostream>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <crystal_constructor/opengl_graphics/mesh.h>
#include <crystal_constructor/crystal_model/crystal_model.h>
#include <crystal_constructor/crystal_model/graphics_crystal_model_view.h>

const unsigned int width = 1000;
const unsigned int height = 800;

namespace {
float currentAspect{(float)width / (float)height};
float lastFrame{0.0f};

float guiAHat[3]{};
float guiBHat[3]{};
float guiCHat[3]{};
} // working variables for graphics loop

void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight)
{
    currentAspect = (float)newWidth / (float)newHeight;
    glViewport(0, 0, newWidth, newHeight);
}  

int main() {

    crystal_constructor::crystal_model::CrystalModel crystalModel{};
    
    guiAHat[0] = crystalModel.GetAHat().x;
    guiAHat[1] = crystalModel.GetAHat().y;
    guiAHat[2] = crystalModel.GetAHat().z;
    
    guiBHat[0] = crystalModel.GetBHat().x;
    guiBHat[1] = crystalModel.GetBHat().y;
    guiBHat[2] = crystalModel.GetBHat().z;
    
    guiCHat[0] = crystalModel.GetCHat().x;
    guiCHat[1] = crystalModel.GetCHat().y;
    guiCHat[2] = crystalModel.GetCHat().z;
    
    crystal_constructor::crystal_model::GraphicsCrystalModelView graphicsCrystalModelView{crystalModel};

    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL Demo", NULL, NULL);

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

    crystal_constructor::opengl_graphics::Shader crystalCellShader{"shaders/crystal_cell_lines.vert", "shaders/crystal_cell_lines.frag"};

    crystal_constructor::crystal_model::CellMeshData initialCellMeshData{graphicsCrystalModelView.GetCellMeshData()};
    crystal_constructor::opengl_graphics::Mesh crystalCell{initialCellMeshData.vertices, initialCellMeshData.indices};

    crystal_constructor::opengl_graphics::Camera camera{currentAspect};

    // Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    
    // // Rendering Loop
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera.SetAspect(currentAspect);
        if (!io.WantCaptureMouse)
        {
            camera.UpdateFromInputs(window, deltaTime);
        }

        crystalModel.SetAHat(crystal_constructor::crystal_model::Vector3{guiAHat[0], guiAHat[1], guiAHat[2]});
        crystalModel.SetBHat(crystal_constructor::crystal_model::Vector3{guiBHat[0], guiBHat[1], guiBHat[2]});
        crystalModel.SetCHat(crystal_constructor::crystal_model::Vector3{guiCHat[0], guiCHat[1], guiCHat[2]});
        crystal_constructor::crystal_model::CellMeshData updatedCellMeshData{graphicsCrystalModelView.GetCellMeshData()};
        crystalCell.SetVertices(updatedCellMeshData.vertices);

        crystalCell.SetModelMatrix(graphicsCrystalModelView.GetModelMatrix());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    
        crystalCell.Draw(crystalCellShader, camera, GL_LINES);

        ImGui::Begin("Crystal Basis");
        ImGui::PushItemWidth(-50);
        ImGui::DragFloat3("A Hat", guiAHat, 0.001f, 0.0f, 0.0f, "%.6f");
        ImGui::DragFloat3("B Hat", guiBHat, 0.001f, 0.0f, 0.0f, "%.6f");
        ImGui::DragFloat3("C Hat", guiCHat, 0.001f, 0.0f, 0.0f, "%.6f");
        if (ImGui::Button("Reset Basis"))
        {
            guiAHat[0] = 1.0f;
            guiAHat[1] = 0.0f;
            guiAHat[2] = 0.0f;

            guiBHat[0] = 0.0f;
            guiBHat[1] = 1.0f;
            guiBHat[2] = 0.0f;

            guiCHat[0] = 0.0f;
            guiCHat[1] = 0.0f;
            guiCHat[2] = 1.0f;
        }
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    crystalCellShader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
