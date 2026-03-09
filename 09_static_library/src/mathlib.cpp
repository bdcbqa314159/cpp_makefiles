#include "mathlib.hpp"
#include <cmath>

namespace mathlib {

double pi() { return M_PI; }
double area_circle(double radius) { return M_PI * radius * radius; }
double circumference(double radius) { return 2.0 * M_PI * radius; }

int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i)
        result *= i;
    return result;
}

}
