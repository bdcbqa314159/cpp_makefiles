# Lesson 03 — Variables

## What you'll learn

How to use Make variables to eliminate repetition and make your Makefile maintainable.

## The problem

In lesson 02, `g++`, `-std=c++20`, and `-Wall -Wextra` appeared in every rule. If you want to switch to `clang++` or add `-O2`, you'd have to change multiple lines. Variables fix this.

## The Makefile

```makefile
CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra
LDFLAGS  =
TARGET   = main
SRCS     = main.cpp greet.cpp
OBJS     = main.o greet.o

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp greet.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp
```

## Standard variable names

These are conventions used by virtually all Makefiles:

| Variable | Purpose | Typical value |
|----------|---------|---------------|
| `CXX` | C++ compiler | `g++`, `clang++` |
| `CXXFLAGS` | Compile flags | `-std=c++20 -Wall -Wextra` |
| `LDFLAGS` | Linker flags | `-L/usr/local/lib` |
| `LDLIBS` | Libraries to link | `-lm -lpthread` |
| `TARGET` | Output name | `main`, `app` |
| `SRCS` | Source files | `main.cpp greet.cpp` |
| `OBJS` | Object files | `main.o greet.o` |

Variables are referenced with `$(VAR)` or `${VAR}`. They're expanded as plain text substitution — no types, no scoping.

## Overriding from the command line

You can override any variable when invoking Make:

```bash
make CXX=clang++                    # use clang instead of g++
make CXXFLAGS="-std=c++20 -O2"     # different flags
```

Command-line values override what's in the Makefile.

## Try it

```bash
cd 03_variables
make            # builds with g++
./main          # Hello, Make variables!
make clean      # removes main and .o files
```

## Files

| File | Purpose |
|------|---------|
| `greet.hpp` | Declares `greet()` |
| `greet.cpp` | Implements it |
| `main.cpp` | Calls `greet()` |
| `Makefile` | Uses variables for compiler, flags, and file lists |
