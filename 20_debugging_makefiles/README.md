# Lesson 20 — Debugging Makefiles

## What you'll learn

How to diagnose Makefile problems using Make's built-in debugging tools: `make -n`, `make -p`, `make --trace`, and the `$(info)`/`$(warning)`/`$(error)` functions.

## The debugging toolkit

### `make -n` — dry run

```bash
make -n
```

Prints every command that Make *would* run, without actually executing them. This is your first tool when a build does something unexpected — you can see exactly what commands Make plans to invoke, with all variables expanded.

```
g++ -std=c++20 -Wall -Wextra -Iinclude -MMD -MP -c -o build/src/logger.o src/logger.cpp
g++ -std=c++20 -Wall -Wextra -Iinclude -MMD -MP -c -o build/src/main.o src/main.cpp
g++ -o build/app build/src/logger.o build/src/main.o
```

If a variable is wrong or a flag is missing, you'll see it here before wasting time on a broken build.

### `make -p` — database dump

```bash
make -p | less
```

Prints Make's entire internal database: all variables (both yours and built-in), all rules (explicit, implicit, and pattern), and all dependencies. This is verbose but comprehensive.

Useful patterns:

```bash
make -p | grep -A2 'CXXFLAGS'     # find your flags
make -p | grep '^[a-z].*:'        # list all targets
make -p | grep -B1 'is up to date'  # see why something didn't rebuild
```

### `make --trace` — trace rebuilds

```bash
make --trace
```

For each target that Make rebuilds, prints why it was rebuilt and what recipe it ran. Less verbose than `make -d` but more informative than default output.

### `make -d` — full debug trace

```bash
make -d 2>&1 | head -100
```

Prints Make's complete decision-making process for every target: which rules it considered, which prerequisites it checked, and why it decided to rebuild (or not). Extremely verbose — pipe to `head` or `less`.

## Debugging functions

These run during Makefile **parsing**, before any recipes execute:

### `$(info text)`

```makefile
$(info [debug] SRCS = $(SRCS))
```

Prints the text to stdout with no prefix. No file/line information. Useful for quick "printf debugging" of variable values.

### `$(warning text)`

```makefile
$(warning SRCS is $(SRCS) — is this right?)
```

Prints with the filename and line number where it appears. Useful when you have multiple included Makefiles and need to know which one is setting a value.

Output: `Makefile:28: SRCS is src/logger.cpp src/main.cpp — is this right?`

### `$(error text)`

```makefile
ifeq ($(SRCS),)
    $(error No source files found in src/)
endif
```

Prints the message and **stops Make immediately**. Use this for guardrails — catching configuration errors early with a clear message instead of a cryptic build failure.

## Common debugging scenarios

### "Why didn't it rebuild?"

```bash
make --trace     # shows what triggered (or didn't trigger) a rebuild
touch src/main.cpp
make --trace     # now shows main.cpp is newer → rebuilds
```

### "What value does this variable have?"

Add temporarily to your Makefile:

```makefile
$(info [debug] OBJS = $(OBJS))
```

Or use the `debug` target in this lesson's Makefile: `make debug`

### "Which rule is being used for this target?"

```bash
make -p | grep -A5 'build/src/main.o'
```

Shows the rule, prerequisites, and recipe for that target.

### "Why is Make doing nothing?"

```bash
make -d 2>&1 | grep -i 'up to date\|newer\|must remake'
```

Shows Make's timestamp comparison decisions.

## The `debug` target

This Makefile includes a `debug` target that prints all resolved variables in a readable format — a quick alternative to `make -p` when you just want to see your own variables.

## Try it

```bash
cd 20_debugging_makefiles
make                    # build normally
make -n clean all       # dry run: see clean + rebuild commands
make debug              # print resolved variables
make --trace            # trace what gets rebuilt (nothing — it's up to date)
touch src/logger.cpp
make --trace            # now logger.o and app rebuild
make clean
```

## Files

| File | Purpose |
|------|---------|
| `include/logger.hpp` | Declares `log_info()`, `log_warn()`, `log_error()` |
| `src/logger.cpp` | Implements logging functions |
| `src/main.cpp` | Demo: logs a few messages |
| `Makefile` | Demonstrates `$(info)`, `$(warning)`, `$(error)`, `debug` target |
