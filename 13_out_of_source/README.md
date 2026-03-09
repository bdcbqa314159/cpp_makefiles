# Lesson 13 — Out-of-Source Builds

## What you'll learn

How to keep all build artifacts (`.o`, `.d`, executables) in a separate `build/` directory, keeping your source tree clean.

## The problem

In lessons 01–12, object files and executables were created alongside source files. This makes it hard to tell what's source and what's generated. `git status` shows clutter. Cleaning requires knowing every artifact type.

## The technique: `BUILDDIR` prefix

All output paths include a `build/` prefix:

```makefile
BUILDDIR = build
OBJS     = $(SRCS:%.cpp=$(BUILDDIR)/%.o)
TARGET   = $(BUILDDIR)/app
```

The source file `src/main.cpp` compiles to `build/src/main.o` — mirroring the directory structure inside `build/`.

## Creating directories on the fly

The `build/src/` directory doesn't exist initially. Each recipe creates it:

```makefile
$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<
```

| Part | Meaning |
|------|---------|
| `@mkdir -p $(@D)` | Create the directory part of the target path. `@` suppresses echoing the command. `-p` creates parents and doesn't error if it exists |
| `$(@D)` | The directory part of `$@`. For `build/src/main.o`, this is `build/src` |

## Clean is trivial

```makefile
clean:
	rm -rf $(BUILDDIR)
```

One command removes everything. No need to list individual file types.

## This is what CMake does

CMake always uses out-of-source builds — `cmake -B build` creates the build directory and puts everything there. Now you understand why.

## Try it

```bash
cd 13_out_of_source
make                    # all artifacts go into build/
ls build/src/           # main.o main.d point.o point.d
./build/app             # a = (0, 0), b = (3, 4), distance = 5
make clean              # rm -rf build/ — done
ls build/ 2>/dev/null   # directory is gone
```

## Files

| File | Purpose |
|------|---------|
| `include/point.hpp` | Declares a `Point` struct with `distance_to()` and `to_string()` |
| `src/point.cpp` | Implements them |
| `src/main.cpp` | Computes distance between two points |
| `Makefile` | Out-of-source builds with `BUILDDIR`, `$(@D)`, `mkdir -p` |
