#pragma once

struct Vec2 {
    double x, y;
    Vec2 operator+(const Vec2& other) const;
    double dot(const Vec2& other) const;
};
