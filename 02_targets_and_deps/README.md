# Lesson 02 — Targets & Dependencies

## What you'll learn

How to compile a multi-file project and understand the two-stage build process: **compile** then **link**.

## Background

When a project has multiple `.cpp` files, the build happens in two stages:

```
main.cpp  ──compile──→  main.o  ──┐
                                   ├──link──→  main (executable)
math.cpp  ──compile──→  math.o  ──┘
```

1. **Compile** (`-c` flag): each `.cpp` is compiled independently into an **object file** (`.o`). This is where syntax errors and type errors are caught.
2. **Link**: the linker combines all `.o` files into a single executable, resolving function calls between files.

The key benefit: if you change only `math.cpp`, Make recompiles only `math.o` and re-links. `main.o` is untouched. For large projects with hundreds of files, this saves significant time.

## The Makefile

```makefile
main: main.o math.o
	g++ -std=c++20 -o main main.o math.o

main.o: main.cpp math.hpp
	g++ -std=c++20 -Wall -Wextra -c main.cpp

math.o: math.cpp math.hpp
	g++ -std=c++20 -Wall -Wextra -c math.cpp
```

Three rules, read bottom-up:
- `math.o` depends on `math.cpp` and `math.hpp` — compile only (`-c`)
- `main.o` depends on `main.cpp` and `math.hpp` — compile only (`-c`)
- `main` depends on both `.o` files — link (no `-c`, produces executable)

Notice that both `.o` files depend on `math.hpp`. If you change the header, both recompile.

## Try it

```bash
cd 02_targets_and_deps
make                # compiles both, then links
./main              # 3 + 4 = 7, 3 * 4 = 12
touch math.cpp      # pretend math.cpp changed
make                # only recompiles math.o, then re-links
make clean          # removes main and all .o files
```

## Files

| File | Purpose |
|------|---------|
| `math.hpp` | Declares `add()` and `multiply()` |
| `math.cpp` | Implements them |
| `main.cpp` | Uses them |
| `Makefile` | Three explicit rules |
