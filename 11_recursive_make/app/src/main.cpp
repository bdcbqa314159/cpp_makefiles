#include <iostream>
#include "ops.hpp"

int main() {
    std::cout << "10 + 3 = " << add(10, 3) << "\n";
    std::cout << "10 - 3 = " << sub(10, 3) << "\n";
    std::cout << "10 * 3 = " << mul(10, 3) << "\n";
    return 0;
}
