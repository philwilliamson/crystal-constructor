#ifndef CRYSTAL_MODEL_H
#define CRYSTAL_MODEL_H

#include <crystal_constructor/crystal_model/vector.h>

namespace crystal_constructor{ namespace crystal_model {

class CrystalModel
{
public:
    CrystalModel() = default;
    void PrintPOSCAR() const;

    CrystalModel& UpdateAHat(Vector3 vector);
    CrystalModel& UpdateBHat(Vector3 vector);
    CrystalModel& UpdateCHat(Vector3 vector);

private:
    Vector3 a_hat_{1.0, 0.0, 0.0};
    Vector3 b_hat_{0.0, 1.0, 0.0};
    Vector3 c_hat_{0.0, 0.0, 1.0};
};

}} // model for storing crystal state

#endif