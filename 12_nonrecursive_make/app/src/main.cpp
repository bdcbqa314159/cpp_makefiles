#include <iostream>
#include "fmt.hpp"

int main() {
    std::cout << fmt::bold("Bold text") << "\n";
    std::cout << fmt::underline("Underlined text") << "\n";
    std::cout << fmt::red("Red text") << "\n";
    return 0;
}
