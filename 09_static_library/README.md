# Lesson 09 — Static Library

## What you'll learn

How to build a static library (`.a` archive), link against it, and understand what happens under the hood.

## What is a static library?

A static library is a bundle of object files (`.o`) packed into a single `.a` file using the `ar` archiver. When you link against it, the linker **copies** the needed code into your executable. The `.a` file is not needed at runtime.

```
mathlib.cpp ──compile──→ mathlib.o ──ar──→ libmathlib.a
                                                │
main.cpp ──compile──→ main.o ──link──→ app      │
                                  ↑              │
                                  └──────────────┘
                                  (copies symbols from .a)
```

## The `ar` command

```makefile
AR      = ar
ARFLAGS = rcs

$(LIB): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^
```

| Flag | Meaning |
|------|---------|
| `r` | **Replace** files in the archive (or add if new) |
| `c` | **Create** the archive if it doesn't exist (suppresses a warning) |
| `s` | Write an object-file **index** (equivalent to running `ranlib`) |

## Linking against a static library

```makefile
$(TARGET): $(APP_OBJS) $(LIB)
	$(CXX) -o $@ $(APP_OBJS) -L. -lmathlib
```

| Flag | Meaning |
|------|---------|
| `-L.` | Add the current directory to the library search path |
| `-lmathlib` | Link `libmathlib.a` (the `lib` prefix and `.a` suffix are implicit) |

**Link order matters.** The linker processes arguments left-to-right. `-lmathlib` must come **after** the object files that reference it. If you put it first, the linker hasn't seen any unresolved symbols yet and skips the library.

## Try it

```bash
cd 09_static_library
make                # compiles mathlib.o, archives into libmathlib.a, links app
./app               # pi, area, circumference, factorial
ar t libmathlib.a   # list contents of the archive
make clean
```

## Files

| File | Purpose |
|------|---------|
| `include/mathlib.hpp` | Declares `pi()`, `area_circle()`, `circumference()`, `factorial()` |
| `src/mathlib.cpp` | Implements them |
| `src/main.cpp` | Uses the library |
| `Makefile` | Builds `.a` with `ar rcs`, links with `-L. -lmathlib` |
