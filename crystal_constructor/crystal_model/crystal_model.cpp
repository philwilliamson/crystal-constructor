#include <iostream>
#include <crystal_constructor/crystal_model/crystal_model.h>

namespace crystal_constructor{ namespace crystal_model {

void CrystalModel::PrintPOSCAR() const {
    std::cout << "POSCAR file written by Crystal Constructor\n";
    std::cout << "1.0\n";
    std::cout << a_hat_.x  << " " << a_hat_.y  << " "  << a_hat_.z << '\n';
    std::cout << b_hat_.x  << " " << b_hat_.y  << " "  << b_hat_.z << '\n';
    std::cout << c_hat_.x  << " " << c_hat_.y  << " "  << c_hat_.z << '\n';
}

CrystalModel& CrystalModel::UpdateAHat(Vector3 vector) {
    a_hat_ = vector;
    return *this;
}

CrystalModel& CrystalModel::UpdateBHat(Vector3 vector) {
    b_hat_ = vector;
    return *this;
}

CrystalModel& CrystalModel::UpdateCHat(Vector3 vector) {
    c_hat_ = vector;
    return *this;
}

}} // model for storing crystal state