# Lesson 12 — Non-Recursive Make

## What you'll learn

How to use a single top-level Makefile that includes fragments from each subdirectory, giving Make a complete dependency graph.

## The problem with recursive Make

In lesson 11, Make runs as separate processes in each directory. It can't see dependencies across boundaries. With `-j4`, it might start building `app` before `libmath` finishes.

The paper **"Recursive Make Considered Harmful"** (Peter Miller, 1998) describes this in detail.

## The solution: `include`

Instead of invoking sub-Makes, a single Makefile includes **module fragments** (`module.mk`) from each directory:

```
12_nonrecursive_make/
├── Makefile                ← single top-level Makefile
├── libfmt/
│   ├── module.mk           ← defines LIBFMT_SRCS, LIBFMT_OBJS, etc.
│   ├── include/fmt.hpp
│   └── src/fmt.cpp
└── app/
    ├── module.mk           ← defines APP_SRCS, APP_OBJS, etc.
    └── src/main.cpp
```

Each `module.mk` uses **full paths** relative to the project root:

```makefile
# libfmt/module.mk
LIBFMT_SRCS = libfmt/src/fmt.cpp
LIBFMT_OBJS = $(LIBFMT_SRCS:.cpp=.o)
LIBFMT_LIB  = libfmt/libfmt.a

$(LIBFMT_LIB): $(LIBFMT_OBJS)
	$(AR) $(ARFLAGS) $@ $^
```

## Critical detail: declare `all` before includes

```makefile
# Declare default target BEFORE includes
all:

include libfmt/module.mk
include app/module.mk

# Wire the dependency after all variables are defined
all: $(APP_BIN)
```

Without this, the first target inside a `module.mk` becomes Make's default target — not what you want.

## Advantages over recursive Make

| Recursive | Non-recursive |
|-----------|--------------|
| Multiple Make processes | Single Make process |
| Manual ordering required | Make resolves order from dependency graph |
| `-j` can break across modules | `-j` works correctly everywhere |
| Can't detect cross-module changes | Full dependency visibility |

## Try it

```bash
cd 12_nonrecursive_make
make            # builds library and app in correct order
./app/app       # bold, underlined, and red text (ANSI codes)
make -j4        # parallel build — works correctly!
make clean
```

## Files

| File | Purpose |
|------|---------|
| `Makefile` | Top-level: sets variables, includes fragments |
| `libfmt/module.mk` | Defines library targets and sources |
| `libfmt/include/fmt.hpp` | ANSI terminal formatting functions |
| `libfmt/src/fmt.cpp` | Implements bold, underline, red |
| `app/module.mk` | Defines app target and sources |
| `app/src/main.cpp` | Uses the formatting library |
