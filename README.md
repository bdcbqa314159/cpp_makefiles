# cpp_makefiles

A progressive, hands-on guide to GNU Make for C++ projects. Each lesson is a self-contained folder with its own Makefile, source files, and README explaining the concepts.

## Prerequisites

- g++ or clang++ with C++20 support
- GNU Make (`make --version`)
- macOS or Linux

### Windows users

These Makefiles use GNU Make, `g++`, and Unix shell commands (`rm`, `mkdir -p`, `uname`). On Windows:

- **WSL** (recommended) — install Ubuntu via WSL, then `sudo apt install g++ make`. Everything works as-is.
- **MSYS2/MinGW** — provides `g++`, `make`, and Unix tools natively on Windows.
- **Learn the concepts, use CMake for builds** — the ideas (targets, dependencies, incremental builds) are universal. Lesson 16 bridges to CMake, which generates the right build files for any platform.

Note: Windows historically used `nmake` (Microsoft's Make) and IDE project files (`.vcxproj`) instead of GNU Make. This platform split is exactly why CMake was created — one description, any build system.

## Lessons

### Phase 1 — Fundamentals

| # | Topic | Key concepts |
|---|-------|-------------|
| [01](01_single_file/) | Single file | Targets, prerequisites, recipes, tab indentation |
| [02](02_targets_and_deps/) | Targets & dependencies | Compile vs link, `.o` files, incremental builds |
| [03](03_variables/) | Variables | `CXX`, `CXXFLAGS`, `LDFLAGS`, `TARGET`, overriding from CLI |
| [04](04_automatic_variables/) | Automatic variables | `$@`, `$<`, `$^`, `$(@D)` |
| [05](05_pattern_rules/) | Pattern rules | `%.o: %.cpp`, substitution references |

### Phase 2 — Real Projects

| # | Topic | Key concepts |
|---|-------|-------------|
| [06](06_src_include/) | Separate src/include | `VPATH`, `-I` include paths |
| [07](07_header_deps/) | Header dependencies | `-MMD -MP`, auto-generated `.d` files, `-include` |
| [08](08_multiple_targets/) | Multiple targets | `all`, `clean`, `rebuild`, `.PHONY` |
| [09](09_static_library/) | Static library | `ar rcs`, `-L`, `-l`, link order |
| [10](10_shared_library/) | Shared library | `-fPIC`, `-shared`, `-rpath`, platform detection |

### Phase 3 — Advanced

| # | Topic | Key concepts |
|---|-------|-------------|
| [11](11_recursive_make/) | Recursive Make | `$(MAKE) -C`, subdirectory Makefiles, ordering |
| [12](12_nonrecursive_make/) | Non-recursive Make | `include`, module fragments, single dependency graph |
| [13](13_out_of_source/) | Out-of-source builds | `BUILDDIR`, `$(@D)`, `mkdir -p` |
| [14](14_conditionals/) | Conditional logic | `ifeq`, `ifdef`, `?=`, `$(error)`, debug/release |
| [15](15_testing/) | Testing | `make test`, exit codes, minimal assert framework |

### Phase 4 — Production Skills

| # | Topic | Key concepts |
|---|-------|-------------|
| [16](16_make_vs_cmake/) | Make vs CMake | Same project built both ways, what CMake automates |
| [17](17_functions/) | Functions & auto-discovery | `$(wildcard)`, `$(patsubst)`, `$(filter)`, `$(foreach)`, `$(call)` |
| [18](18_parallel_builds/) | Parallel builds | `make -j`, order-only prerequisites, `$(MAKE)` propagation |
| [19](19_multiple_executables/) | Multiple executables | Shared library + 2 binaries from one Makefile |
| [20](20_debugging_makefiles/) | Debugging Makefiles | `make -n`, `make -p`, `$(info)`, `$(warning)`, `$(error)` |

## Usage

Each lesson is independent — click a folder to read the explanation, then try it locally:

```bash
cd 01_single_file
make
./main
make clean
```

## Contributing

This is a personal learning project and is not actively seeking contributions. However, if you find a genuine bug or flaw in the code, please do open a pull request — fork the repo, create a feature branch, and submit a PR with a clear description of the fix.
