# cpp_makefiles

A progressive, hands-on guide to GNU Make for C++ projects. Each lesson is a self-contained folder with its own Makefile and source files, building on the previous.

## Prerequisites

- g++ or clang++ with C++23 support
- GNU Make (`make --version`)
- macOS or Linux

## Lessons

### Phase 1 — Fundamentals

| # | Topic | Key concepts |
|---|-------|-------------|
| 01 | Single file | Compiling by hand, then a minimal Makefile |
| 02 | Targets & dependencies | Multiple source files, object files, linking |
| 03 | Variables | `CXX`, `CXXFLAGS`, `LDFLAGS`, `TARGET` |
| 04 | Automatic variables | `$@`, `$<`, `$^`, `$*` |
| 05 | Pattern rules | `%.o: %.cpp`, implicit rules |

### Phase 2 — Real Projects

| # | Topic | Key concepts |
|---|-------|-------------|
| 06 | Separate src/include | `VPATH`, `-I` include paths |
| 07 | Header dependencies | `-MMD -MP`, auto-generated `.d` files |
| 08 | Multiple targets | `all`, `clean`, `rebuild`, `.PHONY` |
| 09 | Static library | `ar rcs`, linking `.a` files |
| 10 | Shared library | `-shared`, `-fPIC`, `RPATH` |

### Phase 3 — Advanced

| # | Topic | Key concepts |
|---|-------|-------------|
| 11 | Recursive Make | Subdirectory Makefiles, `$(MAKE) -C` |
| 12 | Non-recursive Make | Single Makefile, `include` fragments |
| 13 | Out-of-source builds | `BUILDDIR`, `VPATH`, directory creation |
| 14 | Conditional logic | `ifeq`, platform detection, debug/release |
| 15 | Testing | Compile and run tests as a Make target |

### Phase 4 — Bridge to CMake

| # | Topic | Key concepts |
|---|-------|-------------|
| 16 | Make vs CMake | Same project built both ways, side-by-side |

## Usage

Each lesson is independent:

```bash
cd 01_single_file
make
./main
make clean
```

## Contributing

This is a personal learning project and is not actively seeking contributions. However, if you find a genuine bug or flaw in the code, please do open a pull request — fork the repo, create a feature branch, and submit a PR with a clear description of the fix.
