# Lesson 23 — `pkg-config` and Third-Party Libraries

## What you'll learn

How to use `pkg-config` in a Makefile to get the correct compiler and linker flags for third-party libraries, with zlib as a concrete example.

## What is `pkg-config`?

When you install a library (via `apt`, `brew`, `pacman`, etc.), it often ships a `.pc` metadata file. These files live in directories like `/usr/lib/pkgconfig/` or `/usr/local/lib/pkgconfig/` and describe the library's include paths, linker flags, version, and dependencies.

`pkg-config` reads these `.pc` files so you don't have to hardcode paths that vary across systems.

## `--cflags` and `--libs`

The two flags you'll use in every Makefile:

```bash
pkg-config --cflags zlib    # compiler flags: -I paths, defines
pkg-config --libs zlib      # linker flags: -L paths, -l libraries
```

For zlib, this typically returns:

```
--cflags:  (empty — zlib.h is in the standard include path)
--libs:    -lz
```

For a library like SDL2, the output is more interesting:

```
--cflags:  -I/usr/include/SDL2 -D_REENTRANT
--libs:    -lSDL2
```

Other useful queries:

```bash
pkg-config --modversion zlib   # version string, e.g. 1.3.1
pkg-config --exists zlib       # exit code 0 if found, 1 if not
pkg-config --list-all          # every .pc file on the system
```

## The Makefile pattern

The integration follows three steps:

**1. Check existence** using `$(shell ...)`:

```makefile
HAVE_PKGCONFIG := $(shell pkg-config --exists zlib 2>/dev/null && echo yes)
```

**2. Get flags** if available, otherwise set fallbacks:

```makefile
ifeq ($(HAVE_PKGCONFIG),yes)
    ZLIB_CFLAGS := $(shell pkg-config --cflags zlib)
    ZLIB_LIBS   := $(shell pkg-config --libs zlib)
else
    ZLIB_CFLAGS :=
    ZLIB_LIBS   := -lz
endif
```

**3. Append** to the standard variables:

```makefile
CXXFLAGS += $(ZLIB_CFLAGS)
LDFLAGS  += $(ZLIB_LIBS)
```

This pattern works for any library with a `.pc` file. For multiple libraries, repeat the pattern or combine them:

```bash
pkg-config --cflags --libs zlib libpng openssl
```

## Checking for dependencies

The `check-deps` target lets you verify the build environment before compiling:

```bash
make check-deps
```

It reports whether `pkg-config` found zlib, shows the resolved flags, and if `pkg-config` is unavailable, tests the fallback `-lz` flag directly by trying to link a trivial program.

## Fallback strategies

Not every system has `pkg-config` or a `.pc` file for every library. Common fallbacks:

- **Hardcode the flag** (`-lz`) -- works when the library is in a standard path.
- **Use `$(CXX) -x c++ -` test** -- compile a trivial program to check if the library links. The `check-deps` target demonstrates this.
- **`$(error ...)`** -- stop the build early with a clear message if the library is missing entirely.

The Makefile in this lesson tries `pkg-config` first and falls back to `-lz`, which covers most systems where zlib is installed.

## How CMake replaces this

CMake has built-in support for finding libraries without manual `pkg-config` calls:

```cmake
find_package(ZLIB REQUIRED)
target_link_libraries(app PRIVATE ZLIB::ZLIB)
```

`find_package` searches for a CMake config file or uses a built-in `FindZLIB.cmake` module. It handles include paths, linker flags, and version checks automatically. For libraries without CMake support, CMake can still call `pkg-config` via `pkg_check_modules()` from the `PkgConfig` module.

## Try it

```bash
cd 23_pkg_config
make check-deps         # verify zlib is available
make                    # build with pkg-config flags
./build/app             # run: compresses and decompresses a string
make -n                 # dry run: see the resolved flags
make clean
```

## Files

| File | Purpose |
|------|---------|
| `include/compress.hpp` | Declares `compress_data()` and `decompress_data()` |
| `src/compress.cpp` | Implements compression using zlib's `compress()` / `uncompress()` |
| `src/main.cpp` | Demo: compresses a string, decompresses it, verifies round-trip |
| `Makefile` | `pkg-config` integration with fallback, `check-deps` target |
