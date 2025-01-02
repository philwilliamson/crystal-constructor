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

Vector3 CrystalModel::GetAHat() const {
    return a_hat_;
}

Vector3 CrystalModel::GetBHat() const {
    return b_hat_;
}

Vector3 CrystalModel::GetCHat() const {
    return c_hat_;
}

const std::vector<Atom>& CrystalModel::GetAtoms() const {
    return atoms_;
}

CrystalModel& CrystalModel::SetAHat(Vector3 vector) {
    a_hat_ = vector;
    return *this;
}

CrystalModel& CrystalModel::SetBHat(Vector3 vector) {
    b_hat_ = vector;
    return *this;
}

CrystalModel& CrystalModel::SetCHat(Vector3 vector) {
    c_hat_ = vector;
    return *this;
}

CrystalModel& CrystalModel::AddAtom(Atom atom){
    atoms_.insert(atoms_.begin(), atom);
    return *this;
}

CrystalModel& CrystalModel::RemoveAtom(int index){
    atoms_.erase(atoms_.begin() + index);
    return *this;
}

}} // model for storing crystal state