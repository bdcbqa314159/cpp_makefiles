#include <iostream>
#include "point.hpp"

int main() {
    Point a{0.0, 0.0};
    Point b{3.0, 4.0};
    std::cout << "a = " << a.to_string() << "\n";
    std::cout << "b = " << b.to_string() << "\n";
    std::cout << "distance = " << a.distance_to(b) << "\n";
    return 0;
}
