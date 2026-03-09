#include <iostream>
#include "vec.hpp"

int main() {
    Vec2 a{1.0, 2.0};
    Vec2 b{3.0, 4.0};
    Vec2 c = a + b;
    std::cout << "a + b = (" << c.x << ", " << c.y << ")\n";
    std::cout << "a . b = " << a.dot(b) << "\n";
    return 0;
}
