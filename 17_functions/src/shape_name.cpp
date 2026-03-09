#include "shape.hpp"

std::string shape_name(int id) {
    switch (id) {
        case 1: return "circle";
        case 2: return "rectangle";
        case 3: return "triangle";
        default: return "unknown";
    }
}
