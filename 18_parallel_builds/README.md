# Lesson 18 — Parallel Builds

## What you'll learn

How `make -j` runs independent recipes simultaneously, why dependency declarations must be correct for parallel builds to work, and what order-only prerequisites are.

## The idea

Make builds a dependency graph. When you run `make -j4`, Make looks at the graph and runs up to 4 independent recipes at the same time. Compilation steps that don't depend on each other — like compiling `module_a.o` and `module_b.o` — can happen simultaneously.

```
src/module_a.cpp → build/src/module_a.o ─┐
src/module_b.cpp → build/src/module_b.o ─┤
src/module_c.cpp → build/src/module_c.o ─┼── build/app
src/module_d.cpp → build/src/module_d.o ─┤
src/module_e.cpp → build/src/module_e.o ─┤
src/main.cpp     → build/src/main.o     ─┘
```

All 6 `.o` files compile in parallel. The link step waits until all of them are done.

## Using `-j`

```bash
make -j4              # up to 4 parallel jobs
make -j$(nproc)       # all cores (Linux)
make -j$(sysctl -n hw.ncpu)  # all cores (macOS)
make -j               # unlimited — not recommended (can overwhelm the system)
```

The speedup depends on how many independent targets exist and how many cores you have. For 6 independent `.o` files on a 4-core machine, `-j4` compiles ~4x faster than sequential.

## Why correct dependencies matter

Sequential `make` processes rules top-to-bottom. If a dependency is missing from the Makefile, it may still work by accident because the right file was already built in order. With `-j`, that ordering is not guaranteed — Make may build things in any order that satisfies the declared dependencies.

This is the most common source of parallel build bugs: **implicit ordering assumptions that aren't declared in the Makefile**.

## Order-only prerequisites

```makefile
$(BUILDDIR)/%.o: %.cpp | $(BUILDDIR)/src
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILDDIR)/src:
	mkdir -p $@
```

The pipe (`|`) introduces an **order-only prerequisite**. It means:
- The directory must **exist** before the recipe runs
- But changes to the directory's timestamp don't trigger a rebuild

Without the pipe, `mkdir` would update the directory's modification time, which could cause Make to rebuild `.o` files unnecessarily. Order-only prerequisites solve this cleanly.

## `$(MAKE)` in recursive builds

In lesson 11, we used `$(MAKE) -C subdir`. Using `$(MAKE)` instead of `make` is important for parallelism — it propagates the `-j` flag to sub-makes so the total job count is shared across the entire build.

## Try it

```bash
cd 18_parallel_builds
time make                  # sequential build
make clean
time make -j4              # parallel build — compare the time
make clean
make -j4                   # build in parallel
./build/app                # runs the program
make clean
```

## Files

| File | Purpose |
|------|---------|
| `include/modules.hpp` | Declares 5 module functions |
| `src/module_a.cpp` through `src/module_e.cpp` | Independent compilation units |
| `src/main.cpp` | Calls all 5 modules |
| `Makefile` | Demonstrates `-j` parallelism and order-only prerequisites |
