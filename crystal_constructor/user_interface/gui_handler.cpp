#include <crystal_constructor/user_interface/gui_handler.h>

namespace crystal_constructor{ namespace user_interface {

GUIHandler::GUIHandler(const crystal_constructor::crystal_model::CrystalModel& crystalModel, GLFWwindow* window)
    : crystalModel_{crystalModel}
{
    inputBasis_.guiAHat[0] = crystalModel_.GetAHat().x;
    inputBasis_.guiAHat[1] = crystalModel_.GetAHat().y;
    inputBasis_.guiAHat[2] = crystalModel_.GetAHat().z;
    
    inputBasis_.guiBHat[0] = crystalModel_.GetBHat().x;
    inputBasis_.guiBHat[1] = crystalModel_.GetBHat().y;
    inputBasis_.guiBHat[2] = crystalModel_.GetBHat().z;
    
    inputBasis_.guiCHat[0] = crystalModel_.GetCHat().x;
    inputBasis_.guiCHat[1] = crystalModel_.GetCHat().y;
    inputBasis_.guiCHat[2] = crystalModel_.GetCHat().z;

    IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
};

void GUIHandler::Draw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Crystal Basis");
    ImGui::PushItemWidth(-50);
    ImGui::DragFloat3("A Hat", inputBasis_.guiAHat, 0.001f, 0.0f, 0.0f, "%.6f");
    ImGui::DragFloat3("B Hat", inputBasis_.guiBHat, 0.001f, 0.0f, 0.0f, "%.6f");
    ImGui::DragFloat3("C Hat", inputBasis_.guiCHat, 0.001f, 0.0f, 0.0f, "%.6f");
    if (ImGui::Button("Reset Basis"))
    {
        inputBasis_.guiAHat[0] = 1.0f;
        inputBasis_.guiAHat[1] = 0.0f;
        inputBasis_.guiAHat[2] = 0.0f;

        inputBasis_.guiBHat[0] = 0.0f;
        inputBasis_.guiBHat[1] = 1.0f;
        inputBasis_.guiBHat[2] = 0.0f;

        inputBasis_.guiCHat[0] = 0.0f;
        inputBasis_.guiCHat[1] = 0.0f;
        inputBasis_.guiCHat[2] = 1.0f;
    }
    ImGui::End();

    const std::vector<crystal_constructor::crystal_model::Atom>& modelAtoms{crystalModel_.GetAtoms()};

    ImGui::Begin("Atoms");
    ImGui::PushItemWidth(-150);
    if (ImGui::BeginCombo("New Atom Element", elementOptions_.at(guiAddAtomElementIdx_).symbol.c_str()))
    {
        for (int idx = 0; idx < elementOptions_.size(); idx++)
        {
            const bool isSelected = (guiAddAtomElementIdx_ == idx);
            if (ImGui::Selectable(elementOptions_.at(idx).symbol.c_str(), isSelected))
            {
                guiAddAtomElementIdx_ = idx;
            }
            if (isSelected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
    ImGui::DragFloat3("New Atom Coordinates", guiAddAtomCoordinates_, 0.001f, 0.0f, 0.999999f, "%.6f");
    if (ImGui::Button("Add Atom"))
    {
        flags_.addAtomFlag = true;
        // crystalModel.AddAtom(crystal_constructor::crystal_model::Atom{elementOptions.at(guiNewAtomElementIdx_), {guiNewAtomCoordinates[0], guiNewAtomCoordinates[1], guiNewAtomCoordinates[2]}});
    }
    if (ImGui::BeginTable("Atoms List", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY, ImVec2{0.0f, 0.0f}))
    {
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableSetupColumn("Element");
        ImGui::TableSetupColumn("X Coord");
        ImGui::TableSetupColumn("Y Coord");
        ImGui::TableSetupColumn("Z Coord");
        ImGui::TableSetupColumn("Remove?");
        ImGui::TableHeadersRow();

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
                removeAtomIdx_ = idx;
                flags_.removeAtomFlag = true;
                // crystalModel.RemoveAtom(idx);
            }
            ImGui::PopID();
        }
        ImGui::EndTable();
    }
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
};

void GUIHandler::Shutdown() const
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
};

bool GUIHandler::GUICapturedMouse() const
{
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    return io.WantCaptureMouse;
};

InputBasis GUIHandler::GetInputBasis() const
{
    return inputBasis_;
};

crystal_constructor::crystal_model::Atom GUIHandler::GetAddAtomParams() const
{
    crystal_constructor::crystal_model::Atom newAtom{
        elementOptions_.at(guiAddAtomElementIdx_),
        {guiAddAtomCoordinates_[0], guiAddAtomCoordinates_[1], guiAddAtomCoordinates_[2]}
    };

    return newAtom;
};

int GUIHandler::GetRemoveAtomIdx() const
{
    return removeAtomIdx_;
};

GUIFlags GUIHandler::GetFlags() const
{
    return flags_;
};

void GUIHandler::ResetFlags()
{
    flags_.addAtomFlag = false;
    flags_.removeAtomFlag = false;
};

}} // handles gui user inputs