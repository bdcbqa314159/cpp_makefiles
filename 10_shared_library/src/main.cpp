#include <iostream>
#include "strutil.hpp"

int main() {
    std::string text = "Hello Make";
    std::cout << "original: " << text << "\n";
    std::cout << "upper:    " << strutil::to_upper(text) << "\n";
    std::cout << "lower:    " << strutil::to_lower(text) << "\n";
    std::cout << "reverse:  " << strutil::reverse(text) << "\n";
    return 0;
}
