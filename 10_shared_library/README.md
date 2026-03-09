# Lesson 10 — Shared Library

## What you'll learn

How to build a shared library (`.so` on Linux, `.dylib` on macOS), link against it, and handle runtime library loading.

## Static vs shared — what's different?

| Aspect | Static (`.a`) | Shared (`.so`/`.dylib`) |
|--------|--------------|------------------------|
| When code is included | At link time (copied into executable) | At runtime (loaded from disk) |
| Executable size | Larger (contains library code) | Smaller (just a reference) |
| Updating the library | Must re-link the executable | Just replace the `.so`/`.dylib` |
| Runtime requirement | None — self-contained | Library file must exist on disk |

## Key compiler flags

### `-fPIC` — Position Independent Code

Shared libraries can be loaded at any memory address. The code must be compiled so it works regardless of where it's placed:

```makefile
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -MMD -MP -fPIC
```

### `-shared` — produce a shared library

```makefile
$(LIB): $(LIB_OBJS)
	$(CXX) -shared -o $@ $^
```

### `-rpath` — embed the library search path

At runtime, the OS needs to find the `.so`/`.dylib`. Without `-rpath`, you'd have to set `LD_LIBRARY_PATH` (Linux) or `DYLD_LIBRARY_PATH` (macOS) every time. `-rpath` embeds the search path in the executable:

```makefile
# macOS: look next to the executable
RPATH_FLAG = -Wl,-rpath,@executable_path

# Linux: look next to the executable
RPATH_FLAG = -Wl,-rpath,'$$ORIGIN'
```

## Platform detection

Library extensions differ by platform. This Makefile detects the OS:

```makefile
UNAME := $(shell uname)
ifeq ($(UNAME),Darwin)
    LIB = libstrutil.dylib
    RPATH_FLAG = -Wl,-rpath,@executable_path
else
    LIB = libstrutil.so
    RPATH_FLAG = -Wl,-rpath,'$$ORIGIN'
endif
```

`$(shell uname)` runs a shell command and captures the output. `:=` means "evaluate immediately" (not lazily).

## Try it

```bash
cd 10_shared_library
make                        # builds libstrutil.dylib (or .so) and app
./app                       # upper, lower, reverse transformations
otool -L app 2>/dev/null || ldd app    # see runtime library dependencies
make clean
```

## Files

| File | Purpose |
|------|---------|
| `include/strutil.hpp` | Declares `to_upper()`, `to_lower()`, `reverse()` |
| `src/strutil.cpp` | Implements them |
| `src/main.cpp` | Uses the library |
| `Makefile` | `-fPIC`, `-shared`, platform detection, `-rpath` |
