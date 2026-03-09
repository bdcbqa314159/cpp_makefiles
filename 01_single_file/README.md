# Lesson 01 — Single File

## What you'll learn

What a Makefile is, and why you'd use one instead of typing compiler commands by hand.

## Background

To compile a single C++ file, you run:

```bash
g++ -std=c++20 -Wall -Wextra -o main main.cpp
```

This works. But as soon as you have more files, or need to rebuild frequently, typing this gets old. Make automates it.

## The Makefile

```makefile
main: main.cpp
	g++ -std=c++20 -Wall -Wextra -o main main.cpp
```

This defines one **rule** with three parts:

| Part | What it is | In this example |
|------|-----------|-----------------|
| **Target** | What we want to produce | `main` |
| **Prerequisite** | What it depends on | `main.cpp` |
| **Recipe** | How to build it | The `g++` line |

The recipe line **must** start with a tab character, not spaces. This is the most common Makefile syntax error.

## How Make decides to rebuild

Make compares the modification time of the target (`main`) against its prerequisite (`main.cpp`). If `main.cpp` is newer, or `main` doesn't exist, Make runs the recipe. Otherwise it says:

```
make: `main' is up to date.
```

This is the core idea: **dependency-driven incremental builds**.

## The `clean` target

The Makefile also includes a `clean` target:

```makefile
.PHONY: clean
clean:
	rm -f main
```

- `clean` has **no prerequisites** — it always runs its recipe
- `.PHONY: clean` tells Make that `clean` is a command, not a file. Without this, if a file named `clean` existed in the directory, Make would say "clean is up to date" and do nothing. We'll revisit `.PHONY` in detail in [lesson 08](../08_multiple_targets/)
- `rm -f` removes the file silently (no error if it doesn't exist)

## Try it

```bash
cd 01_single_file
make            # builds main
./main          # runs it
make            # "main is up to date" — nothing to do
touch main.cpp  # pretend the source changed
make            # rebuilds
make clean      # removes the executable
```

## Files

| File | Purpose |
|------|---------|
| `main.cpp` | A simple program using `std::format` |
| `Makefile` | The 3-line Makefile |
