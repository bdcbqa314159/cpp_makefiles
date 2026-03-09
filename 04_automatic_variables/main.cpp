#include <iostream>
#include "calc.hpp"

int main() {
    double val = 3.0;
    std::cout << val << "^2 = " << square(val) << "\n";
    std::cout << val << "^3 = " << cube(val) << "\n";
    return 0;
}
