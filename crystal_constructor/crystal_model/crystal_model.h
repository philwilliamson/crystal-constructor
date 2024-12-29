#ifndef CRYSTAL_MODEL_H
#define CRYSTAL_MODEL_H

#include <string>

#include <crystal_constructor/crystal_model/vector.h>

namespace crystal_constructor{ namespace crystal_model {

struct Element {
    std::string symbol{};
    float color[3]{};
};

class CrystalModel
{
public:
    CrystalModel() = default;
    void PrintPOSCAR() const;

    Vector3 GetAHat() const;
    Vector3 GetBHat() const;
    Vector3 GetCHat() const;

    CrystalModel& SetAHat(Vector3 vector);
    CrystalModel& SetBHat(Vector3 vector);
    CrystalModel& SetCHat(Vector3 vector);

private:
    Vector3 a_hat_{1.0, 0.0, 0.0};
    Vector3 b_hat_{0.0, 1.0, 0.0};
    Vector3 c_hat_{0.0, 0.0, 1.0};
};

}} // model for storing crystal state

#endif