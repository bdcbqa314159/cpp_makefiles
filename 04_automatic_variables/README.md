# Lesson 04 — Automatic Variables

## What you'll learn

How to use Make's built-in automatic variables so recipes don't hardcode filenames.

## The problem

In lesson 03, each rule still repeated filenames:

```makefile
main.o: main.cpp calc.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp      # "main.cpp" appears twice
```

Make provides automatic variables that are set for each rule based on the target and prerequisites.

## Automatic variables reference

| Variable | Meaning | Example (for the rule `main.o: main.cpp calc.hpp`) |
|----------|---------|-----------------------------------------------------|
| `$@` | The target | `main.o` |
| `$<` | The **first** prerequisite | `main.cpp` |
| `$^` | **All** prerequisites (deduplicated) | `main.cpp calc.hpp` |
| `$(@D)` | Directory part of `$@` | `.` (or `build/src` for `build/src/main.o`) |
| `$(*)`  | The stem matched by `%` in pattern rules | (covered in lesson 05) |

## The Makefile

```makefile
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^         # $@ = main, $^ = main.o calc.o

main.o: main.cpp calc.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<   # $@ = main.o, $< = main.cpp
```

The recipe is now generic — it works regardless of what the target or prerequisites are named. This is what makes pattern rules (lesson 05) possible.

## Try it

```bash
cd 04_automatic_variables
make            # builds with automatic variables
./main          # 3^2 = 9, 3^3 = 27
make clean
```

## Files

| File | Purpose |
|------|---------|
| `calc.hpp` | Declares `square()` and `cube()` |
| `calc.cpp` | Implements them |
| `main.cpp` | Uses them |
| `Makefile` | Demonstrates `$@`, `$<`, and `$^` |
