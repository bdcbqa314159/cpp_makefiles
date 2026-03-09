#include "app.hpp"
#include <iostream>

void run() {
#ifdef NDEBUG
    std::cout << "Running in RELEASE mode\n";
#else
    std::cout << "Running in DEBUG mode\n";
    std::cout << "  (extra diagnostics enabled)\n";
#endif

#ifdef APP_VERSION
    #define STRINGIFY(x) #x
    #define TOSTRING(x) STRINGIFY(x)
    std::cout << "Version: " << TOSTRING(APP_VERSION) << "\n";
#else
    std::cout << "Version: unknown\n";
#endif
}
