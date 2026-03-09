#include <iostream>
#include "mathlib.hpp"

int main() {
    double r = 5.0;
    std::cout << "pi = " << mathlib::pi() << "\n";
    std::cout << "area(r=" << r << ") = " << mathlib::area_circle(r) << "\n";
    std::cout << "circ(r=" << r << ") = " << mathlib::circumference(r) << "\n";
    std::cout << "6! = " << mathlib::factorial(6) << "\n";
    return 0;
}
