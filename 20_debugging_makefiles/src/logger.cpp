#include "logger.hpp"
#include <iostream>

void log_info(const std::string& msg) {
    std::cout << "[INFO]  " << msg << '\n';
}

void log_warn(const std::string& msg) {
    std::cout << "[WARN]  " << msg << '\n';
}

void log_error(const std::string& msg) {
    std::cerr << "[ERROR] " << msg << '\n';
}
