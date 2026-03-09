# Lesson 17 — Functions & Auto-Discovery

## What you'll learn

How to use Make's built-in functions to auto-discover source files, transform file lists, and define reusable logic — so you never have to manually list every `.cpp` file again.

## The problem

In every lesson so far, we listed source files explicitly:

```makefile
SRCS = main.cpp math.cpp greet.cpp
```

This works, but every time you add a source file, you must also edit the Makefile. In a real project with dozens of files, this is error-prone. Make's functions solve this.

## Key functions

### `$(wildcard pattern)` — find files

```makefile
SRCS = $(wildcard src/*.cpp)
# Result: src/main.cpp src/circle.cpp src/rectangle.cpp ...
```

Make expands the glob and returns all matching files. Add a new `.cpp` to `src/` and it's automatically included — no Makefile edits needed.

### `$(patsubst from,to,text)` — pattern substitution

```makefile
OBJS = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRCS))
# src/main.cpp → build/src/main.o
# src/circle.cpp → build/src/circle.o
```

The `%` wildcard matches any string — it captures a stem and replaces it. This is the full form of the substitution reference shorthand (`$(SRCS:.cpp=.o)`) but more powerful because it can change paths.

### `$(filter pattern,text)` — keep matching words

```makefile
HEADERS = $(filter %.hpp, $(ALL_FILES))
```

Returns only the words that match the pattern. Useful for separating file types from a mixed list.

### `$(filter-out pattern,text)` — remove matching words

```makefile
LIB_SRCS = $(filter-out src/main.cpp, $(SRCS))
```

The opposite of `$(filter)`. Here we remove `main.cpp` from the auto-discovered list so the library sources don't include the `main()` function.

### `$(foreach var,list,body)` — loop over a list

```makefile
DIRS = src include tests
$(foreach d,$(DIRS),$(wildcard $(d)/*.cpp))
```

Iterates over each word in the list, substituting `$(d)` in the body. The results are concatenated. Useful for scanning multiple directories.

### `$(call name,args...)` — user-defined functions

```makefile
announce = @echo "── $(1) ──"

$(TARGET): $(OBJS)
	$(call announce,Linking $@)
	$(CXX) -o $@ $^
```

`$(call)` invokes a variable as a function, substituting `$(1)`, `$(2)`, etc. with the arguments. This lets you define reusable snippets.

### `$(sort list)` and `$(words list)` — utilities

```makefile
$(sort $(SRCS))     # alphabetical sort + deduplication
$(words $(SRCS))    # count: "5"
```

`$(sort)` also removes duplicates, which is useful when combining file lists from multiple sources.

## The Makefile

The key section:

```makefile
# Auto-discover all .cpp files
SRCS = $(wildcard src/*.cpp)

# Remove main.cpp for library-only list
LIB_SRCS = $(filter-out src/main.cpp, $(SRCS))

# Transform .cpp paths to .o paths under build/
OBJS = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRCS))
```

The `info` target shows what each function resolved to — run `make info` to see it.

## `patsubst` vs substitution references

These are equivalent:

```makefile
OBJS = $(SRCS:.cpp=.o)                           # substitution reference
OBJS = $(patsubst %.cpp,%.o,$(SRCS))             # patsubst
```

Use substitution references for simple suffix swaps. Use `$(patsubst)` when you need to change the path (e.g., adding `$(BUILDDIR)/` as a prefix).

## Try it

```bash
cd 17_functions
make            # auto-discovers and builds all .cpp files
./build/app     # runs the program
make info       # shows resolved SRCS, OBJS, file count
make clean
```

Try adding a new source file to see auto-discovery in action:

```bash
# Create a new source file (just needs to compile, doesn't need to be called)
echo 'void placeholder() {}' > src/extra.cpp
make info       # extra.cpp appears automatically in SRCS
make clean
rm src/extra.cpp
```

## Files

| File | Purpose |
|------|---------|
| `include/shape.hpp` | Declares area functions and `shape_name()` |
| `src/circle.cpp` | `circle_area()` |
| `src/rectangle.cpp` | `rectangle_area()` |
| `src/triangle.cpp` | `triangle_area()` |
| `src/shape_name.cpp` | `shape_name()` — maps IDs to names |
| `src/main.cpp` | Demo: computes areas, prints results |
| `Makefile` | Auto-discovery with `$(wildcard)`, `$(patsubst)`, `$(filter-out)`, `$(call)` |
