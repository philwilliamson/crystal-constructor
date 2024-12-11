#include <iostream>
#include <crystal_constructor/crystal_model/crystal_model.h>

namespace crystal_constructor{ namespace crystal_model {

void CrystalModel::PrintPOSCAR() const {
    std::cout << "POSCAR file written by Crystal Constructor\n";
    std::cout << "1.0\n";
    std::cout << a_hat.x  << " " << a_hat.y  << " "  << a_hat.z << '\n';
    std::cout << b_hat.x  << " "  << b_hat.y  << " "  << b_hat.z << '\n';
    std::cout << c_hat.x  << " "  << c_hat.y  << " "  << c_hat.z << '\n';
}

CrystalModel& CrystalModel::UpdateAHat(crystal_constructor::crystal_model::Vector3 vector) {
    a_hat = vector;
    return *this;
}

CrystalModel& CrystalModel::UpdateBHat(crystal_constructor::crystal_model::Vector3 vector) {
    b_hat = vector;
    return *this;
}

CrystalModel& CrystalModel::UpdateCHat(crystal_constructor::crystal_model::Vector3 vector) {
    c_hat = vector;
    return *this;
}

}} // model for storing crystal state