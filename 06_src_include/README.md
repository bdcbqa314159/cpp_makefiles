# Lesson 06 — Separate src/ and include/ Directories

## What you'll learn

How to organize code into `src/` and `include/` directories like real-world projects, and how to tell Make and the compiler where to find things.

## The problem

Lessons 01–05 put everything in one flat directory. Real projects separate:
- **`include/`** — header files (`.hpp`) — the public interface
- **`src/`** — source files (`.cpp`) — the implementation

But now the compiler can't find `#include "counter.hpp"` (it's not in the current directory), and Make can't find `main.cpp` for the pattern rule.

## Two mechanisms

### 1. `-Iinclude` (for the compiler)

Tells the compiler to search `include/` when resolving `#include "..."` directives:

```makefile
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude
```

### 2. `VPATH` (for Make)

Tells Make to search additional directories when it needs a source file:

```makefile
VPATH = src
```

Without `VPATH`, when Make's pattern rule needs `main.cpp` to build `main.o`, it looks in the current directory and fails. With `VPATH = src`, it searches `src/` and finds `src/main.cpp`.

## The Makefile

```makefile
CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude
VPATH    = src

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
```

## Project structure

```
06_src_include/
├── include/
│   └── counter.hpp
├── src/
│   ├── counter.cpp
│   └── main.cpp
└── Makefile
```

## Try it

```bash
cd 06_src_include
make            # compiles from src/, finds headers in include/
./main          # Counter value: 2
make clean
```

## Files

| File | Purpose |
|------|---------|
| `include/counter.hpp` | Declares a `Counter` class |
| `src/counter.cpp` | Implements it |
| `src/main.cpp` | Uses the counter |
| `Makefile` | Uses `VPATH` and `-Iinclude` |
