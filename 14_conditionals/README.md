# Lesson 14 — Conditional Logic

## What you'll learn

How to use Make conditionals for debug/release builds, platform detection, optional features, and error handling.

## Conditional directives

| Directive | Tests | Example |
|-----------|-------|---------|
| `ifeq (a,b)` | String equality | `ifeq ($(BUILD),release)` |
| `ifneq (a,b)` | String inequality | `ifneq ($(CXX),clang++)` |
| `ifdef VAR` | Variable is defined | `ifdef VERSION` |
| `ifndef VAR` | Variable is not defined | `ifndef DEBUG` |

All conditionals end with `endif`. They can nest and use `else if`.

## Debug vs release builds

```makefile
BUILD ?= debug          # ?= sets only if not already defined

ifeq ($(BUILD),release)
    CXXFLAGS += -O2 -DNDEBUG
    BUILDDIR  = build/release
else ifeq ($(BUILD),debug)
    CXXFLAGS += -g -O0 -fsanitize=address
    LDFLAGS  += -fsanitize=address
    BUILDDIR  = build/debug
else
    $(error Unknown BUILD mode: $(BUILD). Use 'debug' or 'release')
endif
```

| Feature | Debug | Release |
|---------|-------|---------|
| Optimization | `-O0` (none) | `-O2` (fast) |
| Debug symbols | `-g` (yes) | No |
| NDEBUG defined | No (asserts active) | Yes (asserts disabled) |
| Address sanitizer | Yes | No |
| Output directory | `build/debug/` | `build/release/` |

## `?=` — default values

```makefile
BUILD ?= debug
```

Sets `BUILD` to `debug` only if it wasn't already set. This lets users override from the command line:

```bash
make BUILD=release
```

## `$(error ...)` — fail fast on bad input

```makefile
$(error Unknown BUILD mode: $(BUILD). Use 'debug' or 'release')
```

Stops Make immediately with a clear error message if someone types `make BUILD=fast`.

## Optional defines

```makefile
ifdef VERSION
    CXXFLAGS += -DAPP_VERSION=$(VERSION)
endif
```

The `VERSION` variable is only available if the user provides it: `make VERSION=1.2.3`.

## Platform detection

```makefile
UNAME := $(shell uname)
ifeq ($(UNAME),Linux)
    CXXFLAGS += -pthread
endif
```

## The `info` target

```makefile
info:
	@echo "BUILD    = $(BUILD)"
	@echo "CXXFLAGS = $(CXXFLAGS)"
```

Prints the resolved configuration. Invaluable for debugging complex Makefiles.

## Try it

```bash
cd 14_conditionals
make                            # debug build (default)
./build/debug/app               # "Running in DEBUG mode"
make BUILD=release VERSION=1.2.3
./build/release/app             # "Running in RELEASE mode, Version: 1.2.3"
make info                       # print resolved config
make BUILD=fast                 # error: unknown build mode
make clean
```

## Files

| File | Purpose |
|------|---------|
| `include/app.hpp` | Declares `run()` |
| `src/app.cpp` | Prints mode (debug/release) and version using preprocessor |
| `src/main.cpp` | Calls `run()` |
| `Makefile` | Conditionals for build mode, platform, version, and error handling |
