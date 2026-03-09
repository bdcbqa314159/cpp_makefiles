# Lesson 16 — Make vs CMake

## What you'll learn

How the same project looks when built with Make and with CMake, side by side. This connects everything from lessons 01–15 to the tool you'll use for production C++ projects.

## The project

A `Matrix2` struct (2×2 matrix) with addition, multiplication, and determinant. An app that demos it, and tests that verify it. Built as a static library + executable + test binary.

## Side-by-side comparison

### The Makefile (~70 lines)

Manually specifies everything:

```makefile
CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -MMD -MP

# Debug/release conditional
BUILD ?= debug
ifeq ($(BUILD),release)
    CXXFLAGS += -O2 -DNDEBUG
endif

# Static library
$(LIB): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^

# Link app against library
$(APP_TARGET): $(APP_OBJS) $(LIB)
	$(CXX) -o $@ $(APP_OBJS) $(LIB)

# Pattern rule for all .cpp → .o
$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Test target
test: $(TEST_TARGET)
	@./$(TEST_TARGET)
```

### The CMakeLists.txt (~25 lines)

Declares what to build, not how:

```cmake
cmake_minimum_required(VERSION 3.20)
project(matrix_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(matrix STATIC src/matrix.cpp)
target_include_directories(matrix PUBLIC include)

add_executable(app src/main.cpp)
target_link_libraries(app PRIVATE matrix)

enable_testing()
add_executable(test_matrix tests/test_matrix.cpp)
target_link_libraries(test_matrix PRIVATE matrix)
add_test(NAME matrix_tests COMMAND test_matrix)
```

## What CMake automates

| Concern | Make (you handle it) | CMake (automatic) |
|---------|---------------------|-------------------|
| Compiler detection | `CXX = g++` | Detects g++/clang++/MSVC |
| Header dependencies | `-MMD -MP`, `-include $(DEPS)` | Always on |
| Out-of-source builds | `BUILDDIR`, `mkdir -p $(@D)` | Always out-of-source |
| Platform differences | `$(shell uname)`, `ifeq` | Handled internally |
| Library extensions | `.a`/`.so`/`.dylib` conditionals | Automatic |
| Parallel builds | Just works with `-j` | Just works with `--parallel` |
| Test runner | Custom `test:` target | `ctest` with reporting |

## What Make gives you

- **Full control.** Every flag, every path, every command is visible. Nothing is hidden behind abstractions.
- **No dependencies.** Make is installed everywhere. CMake must be installed separately.
- **Transparency.** When something breaks, you can read exactly what Make is doing. CMake generates Makefiles (or Ninja files) that are harder to read.

## The tradeoff

CMake adds an abstraction layer. Understanding Make first means you know what's happening underneath when CMake generates a Makefile with `cmake -B build -G "Unix Makefiles"`.

## Try it — with Make

```bash
cd 16_make_vs_cmake
make            # debug build
./build/debug/app
make test       # run tests
make BUILD=release
./build/release/app
make clean
```

## Try it — with CMake

```bash
cd 16_make_vs_cmake
cmake -B cmake_build -DCMAKE_BUILD_TYPE=Release
cmake --build cmake_build
./cmake_build/app
ctest --test-dir cmake_build --output-on-failure
rm -rf cmake_build
```

## Files

| File | Purpose |
|------|---------|
| `include/matrix.hpp` | Declares `Matrix2` with `+`, `*`, `determinant()`, `operator<<` |
| `src/matrix.cpp` | Implements all operations |
| `src/main.cpp` | Demo: addition, multiplication, determinant |
| `tests/test_matrix.cpp` | 3 tests with `ASSERT_NEAR` macro |
| `Makefile` | Full-featured Makefile (everything from lessons 01–15) |
| `CMakeLists.txt` | Same project in CMake (~25 lines) |
