#include "convert.hpp"
#include <iostream>
#include <format>

int main() {
    double temps[] = {0.0, 20.0, 37.0, 100.0};
    std::cout << "Temperature Converter\n";
    std::cout << "---------------------\n";
    for (double c : temps) {
        std::cout << std::format("{:6.1f} C = {:6.1f} F\n",
                                 c, celsius_to_fahrenheit(c));
    }
}
