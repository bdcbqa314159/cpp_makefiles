# Lesson 22 — `$(shell)` and External Tools

## What you'll learn

How to use Make's `$(shell)` function to run external commands during Makefile parsing and embed the results into your build.

## `$(shell)` basics

`$(shell cmd)` executes `cmd` in a subshell and captures its stdout. Newlines in the output are replaced with spaces. The exit status is available in `.SHELLSTATUS` (GNU Make 4.2+).

```makefile
FILES := $(shell ls src/*.cpp)
```

The command runs **during Makefile parsing**, not during recipe execution. This means the result is available as a normal Make variable that you can use anywhere: in other variable definitions, prerequisites, recipes, or conditionals.

## `:=` vs `=` with `$(shell)`

This is the single most important rule when using `$(shell)`:

```makefile
# GOOD — runs once during parsing
GIT_SHA := $(shell git rev-parse --short HEAD)

# BAD — runs every time $(GIT_SHA) is referenced
GIT_SHA = $(shell git rev-parse --short HEAD)
```

With `=` (deferred/recursive assignment), Make stores the expression literally and re-evaluates it each time the variable is referenced. If `$(GIT_SHA)` appears in `CXXFLAGS`, and `CXXFLAGS` is referenced once per source file, the `git` command runs once per source file. On a project with 100 source files, that's 100 unnecessary subprocess spawns.

With `:=` (immediate/simple assignment), the shell command runs exactly once and the result is stored as a plain string. Always use `:=` with `$(shell)`.

## Embedding build metadata

The `-D` compiler flag defines a preprocessor macro. To pass a string value, the quotes must survive from Make through the shell to the compiler:

```makefile
CXXFLAGS += -DGIT_SHA=\"$(GIT_SHA)\"
```

The backslash-escaped quotes `\"` are passed through to the compiler, which sees `-DGIT_SHA="abc1234"`. In C++ code, `GIT_SHA` then expands to the string literal `"abc1234"`.

The C++ source uses `#ifndef` guards so the code compiles even without `-D` flags (falling back to `"unknown"`). This keeps the source buildable outside of Make.

## Error handling

Shell commands can fail. When they do, `$(shell)` returns an empty string. The `2>/dev/null || echo fallback` pattern handles this gracefully:

```makefile
GIT_SHA := $(shell git rev-parse --short HEAD 2>/dev/null || echo unknown)
```

- `2>/dev/null` suppresses stderr so failed commands don't pollute Make's output
- `|| echo unknown` provides a fallback value when the command fails (e.g., building outside a git repo)

Without the fallback, a failed command would produce an empty string, resulting in `-DGIT_SHA=\"\"` — a valid but unhelpful empty define.

## Force-rebuilding build info

There is a subtle problem: `build_info.cpp` doesn't change when you make a new git commit, but the embedded `GIT_SHA` value does. Make's normal timestamp-based rebuild won't trigger because the source file hasn't been modified.

The solution is to add a `FORCE` prerequisite to the object file:

```makefile
$(BUILDDIR)/src/build_info.o: FORCE
FORCE:
```

`FORCE` is a target with no prerequisites and no recipe — it's always considered out of date. Any target that depends on it will always be rebuilt. This is the standard Make idiom for forcing a rebuild without using `.PHONY` (which is meant for targets that don't produce files). Since `build_info.o` is a real file, `FORCE` is the correct approach. The cost is negligible — it's a single small file.

## Try it

```bash
cd 22_shell_external_tools
make info              # see what $(shell) captured
make                   # build with embedded metadata
./build/app            # run — shows git sha, date, hostname
make clean
```

## Files

| File | Purpose |
|------|---------|
| `include/build_info.hpp` | Declares `print_build_info()` |
| `src/build_info.cpp` | Implements build info printing using preprocessor defines with fallback defaults |
| `src/main.cpp` | Calls `print_build_info()` |
| `Makefile` | Demonstrates `$(shell)` for git SHA, date, hostname, and CPU count detection |
