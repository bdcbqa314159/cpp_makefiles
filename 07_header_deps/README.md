# Lesson 07 — Automatic Header Dependencies

## What you'll learn

How to make the compiler auto-generate header dependency information so you never have a stale build.

## The problem

In lesson 06, the pattern rule `%.o: %.cpp` doesn't know about headers. If you change `config.hpp` (which `store.hpp` includes), Make doesn't know that `store.o` and `main.o` need recompiling. The build appears to succeed, but the old code runs. Silent bugs.

You could manually list headers as prerequisites, but that's fragile and tedious.

## The solution: `-MMD` and `-MP`

The compiler can tell Make which headers each source file includes:

```makefile
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -MMD -MP
```

| Flag | What it does |
|------|-------------|
| `-MMD` | Generate a `.d` file alongside each `.o` listing all included headers |
| `-MP` | Add phony targets for each header (prevents errors when headers are renamed/deleted) |

When you compile `store.cpp`, the compiler produces `store.d`:

```makefile
store.o: src/store.cpp include/store.hpp include/config.hpp
```

This is a Make rule! It tells Make that `store.o` depends on those exact files.

## Loading the `.d` files

```makefile
DEPS = $(OBJS:.o=.d)
-include $(DEPS)
```

- `-include` loads the `.d` files if they exist (the `-` prefix means "don't error if they're missing")
- On first build, no `.d` files exist — that's fine, Make compiles everything anyway and creates them
- On subsequent builds, Make reads the `.d` files and knows exactly which headers changed

This is the same technique CMake uses internally.

## Try it

```bash
cd 07_header_deps
make                    # first build — creates .d files
./main                  # HeaderDepsDemo — 3 items
cat store.d             # see the auto-generated dependencies
# Now change MAX_ITEMS in include/config.hpp
make                    # both .o files recompile automatically
make clean
```

## Files

| File | Purpose |
|------|---------|
| `include/config.hpp` | Constants: `MAX_ITEMS`, `APP_NAME` |
| `include/store.hpp` | Declares a `Store` class (includes `config.hpp`) |
| `src/store.cpp` | Implements `Store` |
| `src/main.cpp` | Uses `Store` |
| `Makefile` | `-MMD -MP` flags and `-include $(DEPS)` |
