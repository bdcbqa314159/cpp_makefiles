# Lesson 05 — Pattern Rules

## What you'll learn

How to write one rule that compiles any `.cpp` file into a `.o` file, eliminating per-file rules entirely.

## The problem

In lesson 04, we still wrote a separate rule for each `.o` file. With 50 source files, that's 50 nearly-identical rules. Pattern rules collapse them into one.

## The Makefile

```makefile
SRCS = main.cpp vec.cpp
OBJS = $(SRCS:.cpp=.o)        # text substitution: main.o vec.o

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

%.o: %.cpp                     # pattern rule
	$(CXX) $(CXXFLAGS) -c -o $@ $<
```

## How pattern rules work

The `%` character is a wildcard called the **stem**. When Make needs to build `vec.o`:

1. It matches `vec` against the `%` in `%.o`
2. It looks for `vec.cpp` (substituting the stem into `%.cpp`)
3. It runs the recipe with `$@ = vec.o` and `$< = vec.cpp`

This works for any `.cpp` → `.o` pair. Adding a new source file only requires adding it to `SRCS`.

## Substitution references

```makefile
OBJS = $(SRCS:.cpp=.o)
```

This replaces `.cpp` with `.o` in each word of `SRCS`. So `main.cpp vec.cpp` becomes `main.o vec.o`. No manual synchronization needed.

## Try it

```bash
cd 05_pattern_rules
make            # one pattern rule compiles both files
./main          # a + b = (4, 6), a . b = 11
make clean
```

## Files

| File | Purpose |
|------|---------|
| `vec.hpp` | Declares a `Vec2` struct with `operator+` and `dot()` |
| `vec.cpp` | Implements them |
| `main.cpp` | Creates two vectors and operates on them |
| `Makefile` | Pattern rule `%.o: %.cpp` handles all compilations |
