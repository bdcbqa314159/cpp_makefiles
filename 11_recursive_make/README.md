# Lesson 11 — Recursive Make

## What you'll learn

How to organize a multi-directory project where each subdirectory has its own Makefile, coordinated by a top-level Makefile.

## The pattern

```
11_recursive_make/
├── Makefile              ← top-level: coordinates subdirectories
├── libmath/
│   ├── Makefile          ← builds libmath.a
│   ├── include/ops.hpp
│   └── src/ops.cpp
└── app/
    ├── Makefile          ← builds the executable
    └── src/main.cpp
```

The top-level Makefile doesn't compile anything — it just invokes Make in each subdirectory:

```makefile
all:
	$(MAKE) -C libmath
	$(MAKE) -C app
```

## `$(MAKE) -C dir`

| Part | Meaning |
|------|---------|
| `$(MAKE)` | The Make binary (not hardcoded `make`). This ensures flags like `-j4` and `--silent` propagate to sub-makes |
| `-C dir` | Change to `dir` before reading its Makefile |

## Order matters

The top-level Makefile lists `libmath` before `app` because `app` links against `libmath.a`. If you reversed them, the link step would fail (library doesn't exist yet).

This is the fundamental limitation of recursive Make: **Make can't see dependencies across subdirectories**. With `-j` (parallel builds), it might try to build `app` before `libmath` finishes. The non-recursive approach (lesson 12) solves this.

## When to use recursive Make

It works well for:
- Small-to-medium projects with clear module boundaries
- Projects where subdirectories are independently buildable
- Third-party libraries with their own Makefile

For larger projects or when parallel correctness matters, consider non-recursive Make (lesson 12).

## Try it

```bash
cd 11_recursive_make
make                    # builds libmath, then app
./app/app               # 10 + 3 = 13, etc.
make -C libmath clean   # clean just the library
make clean              # clean everything
```

## Files

| File | Purpose |
|------|---------|
| `Makefile` | Top-level coordinator |
| `libmath/Makefile` | Builds `libmath.a` from `ops.cpp` |
| `libmath/include/ops.hpp` | Declares `add()`, `sub()`, `mul()` |
| `libmath/src/ops.cpp` | Implements them |
| `app/Makefile` | Builds the `app` executable, links against `libmath.a` |
| `app/src/main.cpp` | Uses the library |
