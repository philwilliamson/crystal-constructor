#ifndef GUI_HANDLER_H
#define GUI_HANDLER_H

#include <vector>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <crystal_constructor/crystal_model/crystal_model.h>

namespace crystal_constructor{ namespace user_interface {

struct InputBasis {
    float guiAHat[3]{};
    float guiBHat[3]{};
    float guiCHat[3]{};
};

struct GUIFlags {
    bool addAtomFlag{false};
    bool removeAtomFlag{false};
};

class GUIHandler
{
public:
    explicit GUIHandler(const crystal_constructor::crystal_model::CrystalModel& crystalModel, GLFWwindow* window);

    void Draw();
    void Shutdown() const;

    bool GUICapturedMouse() const;

    InputBasis GetInputBasis() const;
    
    crystal_constructor::crystal_model::Atom GetAddAtomParams() const;

    int GetRemoveAtomIdx() const;

    GUIFlags GetFlags() const;
    void ResetFlags();

private:
    const crystal_constructor::crystal_model::CrystalModel& crystalModel_{};
    
    InputBasis inputBasis_{};
    
    int guiAddAtomElementIdx_{0};
    float guiAddAtomCoordinates_[3]{};
    
    int removeAtomIdx_{};

    GUIFlags flags_{};

    std::vector<crystal_constructor::crystal_model::Element> elementOptions_{
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
};

}} // handles gui user inputs

#endif