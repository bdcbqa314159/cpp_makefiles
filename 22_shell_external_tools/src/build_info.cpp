#include "build_info.hpp"
#include <iostream>

#ifndef GIT_SHA
#define GIT_SHA "unknown"
#endif

#ifndef BUILD_DATE
#define BUILD_DATE "unknown"
#endif

#ifndef BUILD_HOST
#define BUILD_HOST "unknown"
#endif

void print_build_info() {
    std::cout << "Build info:\n"
              << "  git sha:  " << GIT_SHA << '\n'
              << "  date:     " << BUILD_DATE << '\n'
              << "  host:     " << BUILD_HOST << '\n';
}
