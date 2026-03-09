#pragma once
#include <string>

struct Point {
    double x, y;
    double distance_to(const Point& other) const;
    std::string to_string() const;
};
