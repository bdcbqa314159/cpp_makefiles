#include "vec.hpp"

Vec2 Vec2::operator+(const Vec2& other) const {
    return {x + other.x, y + other.y};
}

double Vec2::dot(const Vec2& other) const {
    return x * other.x + y * other.y;
}
