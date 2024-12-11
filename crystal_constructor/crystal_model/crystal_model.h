#ifndef CRYSTAL_MODEL_H
#define CRYSTAL_MODEL_H

#include <crystal_constructor/crystal_model/vector.h>

namespace crystal_constructor{ namespace crystal_model {

class CrystalModel
{

public:
    CrystalModel() = default;
    void PrintPOSCAR() const;

private:
    crystal_constructor::crystal_model::Vector3 a_hat{1.0, 0.0, 0.0};
    crystal_constructor::crystal_model::Vector3 b_hat{0.0, 1.0, 0.0};
    crystal_constructor::crystal_model::Vector3 c_hat{0.0, 0.0, 1.0};
};

}} // model for storing crystal state

#endif