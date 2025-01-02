#include <iostream>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <crystal_constructor/opengl_graphics/mesh.h>
#include <crystal_constructor/crystal_model/crystal_model.h>
#include <crystal_constructor/crystal_model/graphics_crystal_model_view.h>
#include <crystal_constructor/utils/gen_sphere_mesh_data.h>

const unsigned int width = 1280;
const unsigned int height = 720;

namespace {
float currentAspect{(float)width / (float)height};
float lastFrame{0.0f};

float guiAHat[3]{};
float guiBHat[3]{};
float guiCHat[3]{};

int guiNewAtomElementIdx = 0;
float guiNewAtomCoordinates[3]{};

std::vector<crystal_constructor::crystal_model::Element> elementOptions{
    {"H", {(float)1, (float)1, (float)1}},
    {"He", {(float)217/255,(float)1, (float)1}},
    {"Li", {(float)204/255,(float)128/255,(float)255/255}},
    {"Be", {(float)194/255,(float)255/255,(float)0/255}},
    {"B", {(float)255/255,(float)181/255,(float)181/255}},
    {"C", {(float)144/255,(float)144/255,(float)144/255}},
    {"N", {(float)48/255,(float)80/255,(float)248/255}},
    {"O", {(float)255/255,(float)13/255,(float)13/255}},
    {"F", {(float)144/255,(float)224/255,(float)80/255}},
    {"Ne", {(float)179/255,(float)227/255,(float)245/255}},
    {"Na", {(float)171/255,(float)92/255,(float)242/255}},
    {"Mg", {(float)138/255,(float)255/255,(float)0/255}},
    {"Al", {(float)191/255,(float)166/255,(float)166/255}},
    {"Si", {(float)240/255,(float)200/255,(float)160/255}},
    {"P", {(float)255/255,(float)128/255,(float)0/255}},
    {"S", {(float)255/255,(float)255/255,(float)48/255}},
    {"Cl", {(float)31/255,(float)240/255,(float)31/255}},
    {"Ar", {(float)128/255,(float)209/255,(float)227/255}},
    {"K", {(float)143/255,(float)64/255,(float)212/255}},
    {"Ca", {(float)61/255,(float)255/255,(float)0/255}},
    {"Sc", {(float)230/255,(float)230/255,(float)230/255}},
    {"Ti", {(float)191/255,(float)194/255,(float)199/255}},
    {"V", {(float)166/255,(float)166/255,(float)171/255}},
    {"Cr", {(float)138/255,(float)153/255,(float)199/255}},
    {"Mn", {(float)156/255,(float)122/255,(float)199/255}},
    {"Fe", {(float)224/255,(float)102/255,(float)51/255}},
    {"Co", {(float)240/255,(float)144/255,(float)160/255}},
    {"Ni", {(float)80/255,(float)208/255,(float)80/255}},
    {"Cu", {(float)200/255,(float)128/255,(float)51/255}},
    {"Zn", {(float)125/255,(float)128/255,(float)176/255}},
    {"Ga", {(float)194/255,(float)143/255,(float)143/255}},
    {"Ge", {(float)102/255,(float)143/255,(float)143/255}},
    {"As", {(float)189/255,(float)128/255,(float)227/255}},
    {"Se", {(float)255/255,(float)161/255,(float)0/255}},
    {"Br", {(float)166/255,(float)41/255,(float)41/255}},
    {"Kr", {(float)92/255,(float)184/255,(float)209/255}},
    {"Rb", {(float)112/255,(float)46/255,(float)176/255}},
    {"Sr", {(float)0/255,(float)255/255,(float)0/255}},
    {"Y", {(float)148/255,(float)255/255,(float)255/255}},
    {"Zr", {(float)148/255,(float)224/255,(float)224/255}},
    {"Nb", {(float)115/255,(float)194/255,(float)201/255}},
    {"Mo", {(float)84/255,(float)181/255,(float)181/255}},
    {"Tc", {(float)59/255,(float)158/255,(float)158/255}},
    {"Ru", {(float)36/255,(float)143/255,(float)143/255}},
    {"Rh", {(float)10/255,(float)125/255,(float)140/255}},
    {"Pd", {(float)0/255,(float)105/255,(float)133/255}},
    {"Ag", {(float)192/255,(float)192/255,(float)192/255}},
    {"Cd", {(float)255/255,(float)217/255,(float)143/255}},
    {"In", {(float)166/255,(float)117/255,(float)115/255}},
    {"Sn", {(float)102/255,(float)128/255,(float)128/255}},
    {"Sb", {(float)158/255,(float)99/255,(float)181/255}},
    {"Te", {(float)212/255,(float)122/255,(float)0/255}},
    {"I", {(float)148/255,(float)0/255,(float)148/255}},
    {"Xe", {(float)66/255,(float)158/255,(float)176/255}},
    {"Cs", {(float)87/255,(float)23/255,(float)143/255}},
    {"Ba", {(float)0/255,(float)201/255,(float)0/255}},
    {"La", {(float)112/255,(float)212/255,(float)255/255}},
    {"Ce", {(float)255/255,(float)255/255,(float)199/255}},
    {"Pr", {(float)217/255,(float)255/255,(float)199/255}},
    {"Nd", {(float)199/255,(float)255/255,(float)199/255}},
    {"Pm", {(float)163/255,(float)255/255,(float)199/255}},
    {"Sm", {(float)143/255,(float)255/255,(float)199/255}},
    {"Eu", {(float)97/255,(float)255/255,(float)199/255}},
    {"Gd", {(float)69/255,(float)255/255,(float)199/255}},
    {"Tb", {(float)48/255,(float)255/255,(float)199/255}},
    {"Dy", {(float)31/255,(float)255/255,(float)199/255}},
    {"Ho", {(float)0/255,(float)255/255,(float)156/255}},
    {"Er", {(float)0/255,(float)230/255,(float)117/255}},
    {"Tm", {(float)0/255,(float)212/255,(float)82/255}},
    {"Yb", {(float)0/255,(float)191/255,(float)56/255}},
    {"Lu", {(float)0/255,(float)171/255,(float)36/255}},
    {"Hf", {(float)77/255,(float)194/255,(float)255/255}},
    {"Ta", {(float)77/255,(float)166/255,(float)255/255}},
    {"W", {(float)33/255,(float)148/255,(float)214/255}},
    {"Re", {(float)38/255,(float)125/255,(float)171/255}},
    {"Os", {(float)38/255,(float)102/255,(float)150/255}},
    {"Ir", {(float)23/255,(float)84/255,(float)135/255}},
    {"Pt", {(float)208/255,(float)208/255,(float)224/255}},
    {"Au", {(float)255/255,(float)209/255,(float)35/255}},
    {"Hg", {(float)184/255,(float)184/255,(float)208/255}},
    {"Tl", {(float)166/255,(float)84/255,(float)77/255}},
    {"Pb", {(float)87/255,(float)89/255,(float)97/255}},
    {"Bi", {(float)158/255,(float)79/255,(float)181/255}},
    {"Po", {(float)171/255,(float)92/255,(float)0/255}},
    {"At", {(float)117/255,(float)79/255,(float)69/255}},
    {"Rn", {(float)66/255,(float)130/255,(float)150/255}},
    {"Fr", {(float)66/255,(float)0/255,(float)102/255}},
    {"Ra", {(float)0/255,(float)125/255,(float)0/255}},
    {"Ac", {(float)112/255,(float)171/255,(float)250/255}},
    {"Th", {(float)0/255,(float)186/255,(float)255/255}},
    {"Pa", {(float)0/255,(float)161/255,(float)255/255}},
    {"U", {(float)0/255,(float)143/255,(float)255/255}},
    {"Np", {(float)0/255,(float)128/255,(float)255/255}},
    {"Pu", {(float)0/255,(float)107/255,(float)255/255}},
    {"Am", {(float)84/255,(float)92/255,(float)242/255}},
    {"Cm", {(float)120/255,(float)92/255,(float)227/255}},
    {"Bk", {(float)138/255,(float)79/255,(float)227/255}},
    {"Cf", {(float)161/255,(float)54/255,(float)212/255}},
    {"Es", {(float)179/255,(float)31/255,(float)212/255}},
    {"Fm", {(float)179/255,(float)31/255,(float)186/255}},
    {"Md", {(float)179/255,(float)13/255,(float)166/255}},
    {"No", {(float)189/255,(float)13/255,(float)135/255}},
    {"Lr", {(float)199/255,(float)0/255,(float)102/255}},
    {"Rf", {(float)204/255,(float)0/255,(float)89/255}},
    {"Db", {(float)209/255,(float)0/255,(float)79/255}},
    {"Sg", {(float)217/255,(float)0/255,(float)69/255}},
    {"Bh", {(float)224/255,(float)0/255,(float)56/255}},
    {"Hs", {(float)230/255,(float)0/255,(float)46/255}},
    {"Mt", {(float)235/255,(float)0/255,(float)38/255}},
    {"Ds", {(float)240/255,(float)0/255,(float)28/255}},
    {"Rg", {(float)245/255,(float)0/255,(float)18/255}},
    {"Cn", {(float)250/255,(float)0/255,(float)8/255}},
    {"Nh", {(float)255/255,(float)0/255,(float)0/255}},
};
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

    crystal_constructor::opengl_graphics::MeshData initialCellMeshData{graphicsCrystalModelView.GetCellMeshData()};
    crystal_constructor::opengl_graphics::Mesh crystalCellMesh{initialCellMeshData.vertices, initialCellMeshData.indices};

    crystal_constructor::opengl_graphics::Shader atomShader{"shaders/atom.vert", "shaders/atom.frag"};

    crystal_constructor::opengl_graphics::MeshData sphereMeshData{crystal_constructor::utils::gen_sphere_mesh_data(0.1f,50,50)};
    crystal_constructor::opengl_graphics::Mesh atomMesh{sphereMeshData.vertices, sphereMeshData.indices};

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
        crystal_constructor::opengl_graphics::MeshData updatedCellMeshData{graphicsCrystalModelView.GetCellMeshData()};
        crystalCellMesh.SetVertices(updatedCellMeshData.vertices);

        crystalCellMesh.SetModelMatrix(graphicsCrystalModelView.GetModelMatrix());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    
        crystalCellMesh.Draw(crystalCellShader, camera, GL_LINES);

        const std::vector<crystal_constructor::crystal_model::AtomDrawData> modelAtomsDrawData{graphicsCrystalModelView.GetAtomsUniformData()};

        for (int idx = 0; idx < modelAtomsDrawData.size(); idx++)
        {
            crystal_constructor::crystal_model::AtomDrawData currentAtomDrawData{modelAtomsDrawData.at(idx)};

            atomShader.UpdateUniform3fv("atomColor", currentAtomDrawData.color);
            atomMesh.SetModelMatrix(currentAtomDrawData.modelMatrix);

            atomMesh.Draw(atomShader, camera);
        }
        

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

        const std::vector<crystal_constructor::crystal_model::Atom>& modelAtoms{crystalModel.GetAtoms()};

        ImGui::Begin("Atoms");
        ImGui::PushItemWidth(-150);
        if (ImGui::BeginCombo("New Atom Element", elementOptions.at(guiNewAtomElementIdx).symbol.c_str()))
        {
            for (int idx = 0; idx < elementOptions.size(); idx++)
            {
                const bool isSelected = (guiNewAtomElementIdx == idx);
                if (ImGui::Selectable(elementOptions.at(idx).symbol.c_str(), isSelected))
                {
                    guiNewAtomElementIdx = idx;
                }
                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        ImGui::DragFloat3("New Atom Coordinates", guiNewAtomCoordinates, 0.001f, 0.0f, 0.999999f, "%.6f");
        if (ImGui::Button("Add Atom"))
        {
            crystalModel.AddAtom(crystal_constructor::crystal_model::Atom{elementOptions.at(guiNewAtomElementIdx), {guiNewAtomCoordinates[0], guiNewAtomCoordinates[1], guiNewAtomCoordinates[2]}});
        }
        if (ImGui::BeginTable("Atoms List", 5))
        {
            ImGui::TableSetupColumn("Element");
            ImGui::TableSetupColumn("Position");

            for (int idx = 0; idx < modelAtoms.size(); idx++)
            {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text(modelAtoms.at(idx).element.symbol.c_str());
                ImGui::TableNextColumn();
                ImGui::Text("%.6f", modelAtoms.at(idx).position.x);
                ImGui::TableNextColumn();
                ImGui::Text("%.6f", modelAtoms.at(idx).position.y);
                ImGui::TableNextColumn();
                ImGui::Text("%.6f", modelAtoms.at(idx).position.z);
                ImGui::TableNextColumn();
                ImGui::PushID(idx);
                if (ImGui::Button("Remove"))
                {
                    crystalModel.RemoveAtom(idx);
                }
                ImGui::PopID();
            }
            ImGui::EndTable();
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
