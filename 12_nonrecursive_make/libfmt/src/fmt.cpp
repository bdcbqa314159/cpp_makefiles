#include "fmt.hpp"

namespace fmt {

std::string bold(const std::string& s) {
    return "\033[1m" + s + "\033[0m";
}

std::string underline(const std::string& s) {
    return "\033[4m" + s + "\033[0m";
}

std::string red(const std::string& s) {
    return "\033[31m" + s + "\033[0m";
}

}
