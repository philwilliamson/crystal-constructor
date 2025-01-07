#ifndef CRYSTAL_MODEL_H
#define CRYSTAL_MODEL_H

#include <vector>
#include <string>

#include <crystal_constructor/crystal_model/vector.h>

namespace crystal_constructor{ namespace crystal_model {

struct Element {
    std::string symbol{};
    float color[3]{};
};

struct Atom {
    Element element{};
    Vector3 position{};
};

class CrystalModel
{
public:
    CrystalModel() = default;
    void PrintPOSCAR() const;

    Vector3 GetAHat() const;
    Vector3 GetBHat() const;
    Vector3 GetCHat() const;

    const std::vector<Atom>& GetAtoms() const;

    CrystalModel& SetAHat(Vector3 vector);
    CrystalModel& SetBHat(Vector3 vector);
    CrystalModel& SetCHat(Vector3 vector);
    
    CrystalModel& AddOnAtom(Atom atom);
    CrystalModel& RemoveAtom(int index);

private:
    Vector3 a_hat_{1.0, 0.0, 0.0};
    Vector3 b_hat_{0.0, 1.0, 0.0};
    Vector3 c_hat_{0.0, 0.0, 1.0};

    std::vector<Atom> atoms_{};
};

}} // model for storing crystal state

#endif