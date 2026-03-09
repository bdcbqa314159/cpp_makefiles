#include "point.hpp"
#include <cmath>
#include <sstream>

double Point::distance_to(const Point& other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

std::string Point::to_string() const {
    std::ostringstream oss;
    oss << "(" << x << ", " << y << ")";
    return oss.str();
}
