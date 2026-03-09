#include "shape.hpp"
#include <iostream>
#include <format>

int main() {
    std::cout << std::format("Circle (r=5):      {:.2f}\n", circle_area(5.0));
    std::cout << std::format("Rectangle (3x4):   {:.2f}\n", rectangle_area(3.0, 4.0));
    std::cout << std::format("Triangle (6, h=4): {:.2f}\n", triangle_area(6.0, 4.0));
    std::cout << std::format("Shape 2 is: {}\n", shape_name(2));
}
