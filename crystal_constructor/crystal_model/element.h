#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

namespace crystal_constructor{ namespace crystal_model {

struct Element {
    std::string symbol{};
    float color[3]{};
};

}} // struct for holding information about chemical elements

#endif