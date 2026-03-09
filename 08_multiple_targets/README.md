# Lesson 08 — Multiple Targets

## What you'll learn

How to define multiple build targets (`all`, `clean`, `rebuild`) and why `.PHONY` matters.

## Conventional targets

Most Makefiles define these standard targets:

| Target | Purpose |
|--------|---------|
| `all` | Build everything (the default — must be first in the file) |
| `clean` | Remove all build artifacts |
| `rebuild` | Clean then build from scratch |
| `test` | Build and run tests (lesson 15) |
| `install` | Copy files to system directories |

## Why `app` instead of `main`?

In lessons 01–07 the executable was called `main` — matching the single source file. From this lesson onward, projects have multiple source files (logger, app, etc.), so the executable is named `app` to reflect that it's a complete application, not just one file. The name is arbitrary — what matters is that `TARGET` holds it.

## `.PHONY` — why it matters

```makefile
.PHONY: all clean rebuild
```

Without `.PHONY`, if a file named `clean` happened to exist in your directory, Make would check its timestamp, see it's "up to date," and skip the recipe. `.PHONY` tells Make these targets are commands, not files — always run them.

## Default target

The **first target** in the Makefile is what `make` (with no arguments) builds. Convention is to name it `all`:

```makefile
all: $(TARGET)    # this is the default target
```

## The Makefile

```makefile
.PHONY: all clean rebuild

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

rebuild: clean all
```

## Try it

```bash
cd 08_multiple_targets
make              # builds the app (default target: all)
./app             # [INFO]  Application started ...
make clean        # removes app, .o, and .d files
make rebuild      # cleans, then builds fresh
```

## Files

| File | Purpose |
|------|---------|
| `include/logger.hpp` | Declares `log_info()` and `log_error()` |
| `src/logger.cpp` | Implements them with `[INFO]`/`[ERROR]` prefixes |
| `src/main.cpp` | Logs several messages |
| `Makefile` | `all`, `clean`, `rebuild` targets with `.PHONY` |
