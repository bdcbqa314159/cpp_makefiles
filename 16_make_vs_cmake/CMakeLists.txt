# Lesson 16: Make vs CMake — the CMake version
#
# Compare this with the Makefile in the same directory.
# CMake handles automatically:
#   - Compiler detection (g++, clang++, MSVC)
#   - Header dependency tracking
#   - Out-of-source builds (always)
#   - Platform differences (library extensions, flags)
#   - Parallel builds
#   - Test registration
#
# What took ~70 lines in the Makefile is ~25 lines here.
# The tradeoff: CMake is a build system generator (it
# produces Makefiles/Ninja files), adding a layer of
# indirection. Understanding Make first makes CMake's
# output and behavior much less mysterious.

cmake_minimum_required(VERSION 3.20)
project(matrix_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Static library — replaces: ar rcs, LIB_SRCS, pattern rules
add_library(matrix STATIC src/matrix.cpp)
target_include_directories(matrix PUBLIC include)

# Executable — replaces: APP_TARGET, linking, RPATH
add_executable(app src/main.cpp)
target_link_libraries(app PRIVATE matrix)

# Tests — replaces: TEST_TARGET, test phony target
enable_testing()
add_executable(test_matrix tests/test_matrix.cpp)
target_link_libraries(test_matrix PRIVATE matrix)
add_test(NAME matrix_tests COMMAND test_matrix)
