#include <iostream>
#include "matrix.hpp"

int main() {
    Matrix2 a{1, 2, 3, 4};
    Matrix2 b{5, 6, 7, 8};
    std::cout << "a     = " << a << "\n";
    std::cout << "b     = " << b << "\n";
    std::cout << "a + b = " << (a + b) << "\n";
    std::cout << "a * b = " << (a * b) << "\n";
    std::cout << "det(a)= " << a.determinant() << "\n";
    return 0;
}
