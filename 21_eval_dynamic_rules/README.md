# Lesson 21 — `$(eval)` and Dynamic Rules

## What you'll learn

How to use `$(eval)`, `$(call)`, and `$(foreach)` to generate Makefile rules from a template, eliminating repetitive boilerplate when building multiple similar targets.

## The problem

In lesson 19, each executable required its own block of variables and a hand-written link rule:

```makefile
TEMP_SRCS = src/temp_tool.cpp
TEMP_OBJS = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(TEMP_SRCS))
TEMP_BIN  = $(BUILDDIR)/temp_tool

$(TEMP_BIN): $(TEMP_OBJS) $(LIB)
	@mkdir -p $(@D)
	$(CXX) -o $@ $(TEMP_OBJS) $(LIB)
```

Two executables means two nearly-identical blocks. Three means three. Ten means ten. Every new program is copy-paste with a find-and-replace on the name, which is tedious and error-prone.

## The solution: `$(eval)` + `$(call)` + `$(foreach)`

The idea is to write the boilerplate **once** as a template, then stamp it out for each program in a list.

### 1. Define the template

```makefile
define make_program
$(1)_SRCS = src/$(1).cpp
$(1)_OBJS = $$(patsubst %.cpp,$$(BUILDDIR)/%.o,$$($(1)_SRCS))
$(1)_BIN  = $$(BUILDDIR)/$(1)

$$($(1)_BIN): $$($(1)_OBJS) $$(LIB)
	@mkdir -p $$(@D)
	$$(CXX) -o $$@ $$($(1)_OBJS) $$(LIB)
endef
```

`$(1)` is the first argument passed to `$(call)`. Everything else follows the `$$` escaping rules described below.

### 2. Stamp out the rules

```makefile
PROGRAMS = server client admin
$(foreach prog,$(PROGRAMS),$(eval $(call make_program,$(prog))))
```

This single line replaces all three hand-written blocks. To add a fourth program, just append its name to `PROGRAMS` and create `src/name.cpp`.

### 3. Collect derived variables

```makefile
ALL_BINS = $(foreach prog,$(PROGRAMS),$($(prog)_BIN))
ALL_OBJS = $(LIB_OBJS) $(foreach prog,$(PROGRAMS),$($(prog)_OBJS))
```

`$($(prog)_BIN)` is a double expansion: first `$(prog)` expands to `server`, then `$(server_BIN)` expands to the actual path. This works because `$(eval)` already defined those variables.

## How `$$` escaping works

The `$(call)` + `$(eval)` pipeline processes the template in two passes:

| Pass | When | What `$` does |
|------|------|---------------|
| **First pass** (`$(call)` + `$(eval)`) | Makefile parse time | Single `$` is expanded. `$(1)` becomes the argument. `$$` becomes a literal `$`. |
| **Second pass** (Make's normal evaluation) | Rule/recipe execution time | The surviving `$` expressions are expanded as usual. |

Concrete example inside the template:

| You write | After first pass (eval time) | After second pass (recipe time) |
|-----------|-----------------------------|---------------------------------|
| `$(1)` | `server` | (already resolved) |
| `$$(CXX)` | `$(CXX)` | `g++` |
| `$$(@D)` | `$(@D)` | `build` |
| `$$($(1)_OBJS)` | `$(server_OBJS)` | `build/src/server.o` |

The rule of thumb: use single `$` for things that should resolve **during eval** (template arguments like `$(1)`), and double `$$` for things that should resolve **later** (Make variables, automatic variables, and function calls).

## Watch out: default goal

`$(eval)` creates rules at parse time. If the first `$(eval)`-generated rule appears before your `all:` target, Make will treat it as the default goal and only build that one program. Fix this by setting `.DEFAULT_GOAL = all` before the `$(foreach)` line.

## Debugging eval'd rules

To see what the template expands to **before** `$(eval)` interprets it, temporarily replace `$(eval ...)` with `$(info ...)`:

```makefile
$(foreach prog,$(PROGRAMS),$(info $(call make_program,$(prog))))
```

This prints the generated Makefile text to stdout without actually defining any rules. You can verify that the variable names, prerequisites, and recipes look correct. Once satisfied, switch back to `$(eval ...)`.

## Try it

```bash
cd 21_eval_dynamic_rules
make                    # builds all three programs
./build/server          # [server] Running MyApp v1.0
./build/client          # [client] Connected to MyApp v1.0
./build/admin           # [admin] Managing MyApp v1.0
make clean
```

To add a new program, just add its name to `PROGRAMS` and create `src/name.cpp`. No Makefile rules to copy.

## Files

| File | Purpose |
|------|---------|
| `include/config.hpp` | Declares `get_app_name()` |
| `src/config.cpp` | Implements `get_app_name()`, shared by all programs |
| `src/server.cpp` | Server executable |
| `src/client.cpp` | Client executable |
| `src/admin.cpp` | Admin executable |
| `Makefile` | Demonstrates `$(eval)` + `$(call)` + `$(foreach)` to generate per-program rules |
