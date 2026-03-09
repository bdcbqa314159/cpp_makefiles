#include "convert.hpp"
#include <iostream>
#include <format>

int main() {
    double distances[] = {1.0, 5.0, 10.0, 42.195};
    std::cout << "Distance Converter\n";
    std::cout << "-------------------\n";
    for (double km : distances) {
        std::cout << std::format("{:7.2f} km = {:7.2f} mi\n",
                                  km, km_to_miles(km));
    }
}
