#include "greet.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: greeter <name>\n";
        return 1;
    }
    std::cout << greet(argv[1]) << '\n';
}
