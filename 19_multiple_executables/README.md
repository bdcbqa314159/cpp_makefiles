# Lesson 19 — Multiple Executables

## What you'll learn

How to build multiple executables from a single Makefile, sharing a common library. This is the typical layout for projects that produce both a main application and supporting tools.

## The pattern

```makefile
# Define each executable's sources separately
TEMP_SRCS = src/temp_tool.cpp
DIST_SRCS = src/dist_tool.cpp

# Build shared code into a library
LIB = $(BUILDDIR)/libconvert.a

# Each executable links its objects + the library
$(TEMP_BIN): $(TEMP_OBJS) $(LIB)
	$(CXX) -o $@ $(TEMP_OBJS) $(LIB)

$(DIST_BIN): $(DIST_OBJS) $(LIB)
	$(CXX) -o $@ $(DIST_OBJS) $(LIB)

# `all` builds everything
all: $(TEMP_BIN) $(DIST_BIN)
```

## Why a library?

Both executables use the same conversion functions. Without a library, you'd either:
- Compile `convert.cpp` twice (once per executable) — wasteful
- List `convert.o` in both link lines — works but doesn't scale

A static library packages the shared code once. Both executables link against it. If the library source changes, it recompiles once, and both executables re-link.

## The dependency graph

```
src/convert.cpp → build/src/convert.o → build/libconvert.a ─┐
                                                             ├── build/temp_tool
src/temp_tool.cpp → build/src/temp_tool.o ───────────────────┘

src/convert.cpp → build/src/convert.o → build/libconvert.a ─┐
                                                             ├── build/dist_tool
src/dist_tool.cpp → build/src/dist_tool.o ───────────────────┘
```

With `make -j`, both executables can link in parallel once the library is ready.

## Key decisions

**Separate source lists, not `$(wildcard)`:** When a project has multiple `main()` functions, you can't just `$(wildcard src/*.cpp)` and link everything together — the linker would see duplicate `main` symbols. Each executable needs its own source list. Use `$(wildcard)` for library sources, and list executable sources explicitly.

**One pattern rule handles all `.o` files:** Even though the object files belong to different targets, the same `%.o: %.cpp` rule compiles them all. Make figures out which ones to build based on what each target needs.

## Adding a third executable

To add another tool, you only need to:

1. Create the source file (e.g., `src/speed_tool.cpp`)
2. Add 3 lines to the Makefile:

```makefile
SPEED_SRCS = src/speed_tool.cpp
SPEED_OBJS = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SPEED_SRCS))
SPEED_BIN  = $(BUILDDIR)/speed_tool
```

3. Add the link rule and add it to `all`:

```makefile
$(SPEED_BIN): $(SPEED_OBJS) $(LIB)
	@mkdir -p $(@D)
	$(CXX) -o $@ $(SPEED_OBJS) $(LIB)

all: $(TEMP_BIN) $(DIST_BIN) $(SPEED_BIN)
```

## Try it

```bash
cd 19_multiple_executables
make                    # builds both tools
./build/temp_tool       # temperature converter
./build/dist_tool       # distance converter
make clean
```

## Files

| File | Purpose |
|------|---------|
| `include/convert.hpp` | Declares temperature and distance conversion functions |
| `src/convert.cpp` | Implements all conversions |
| `src/temp_tool.cpp` | Executable 1: temperature converter |
| `src/dist_tool.cpp` | Executable 2: distance converter |
| `Makefile` | Builds a static library + 2 executables |
