# Lesson 15 — Testing

## What you'll learn

How to set up a `make test` target that compiles and runs a test suite, with the build failing if any test fails.

## The pattern

```makefile
test: $(TEST_TARGET)
	@echo "Running tests..."
	@./$(TEST_TARGET)
```

If the test binary exits with a non-zero status (test failure), Make reports an error and stops. This makes it safe to use in CI: `make test` returns a non-zero exit code on failure.

## Three build commands

| Command | What it does |
|---------|-------------|
| `make` | Build the app only (default target) |
| `make test` | Build the test binary and run it |
| `make all` | Build both app and test binaries (but don't run tests) |

## Test framework

This lesson uses a minimal homemade test framework — no external dependencies. Three assertion macros:

```cpp
ASSERT_EQ(actual, expected)     // equality check
ASSERT_TRUE(expr)               // boolean check
ASSERT_THROWS(expr)             // expects an exception
```

Each test is a plain function. Failures print the file, line, and values. The `main()` function runs all tests and returns 1 if any failed.

For real projects, you'd use a framework like [Catch2](https://github.com/catchorg/Catch2) or [Google Test](https://github.com/google/googletest). The Makefile structure is the same — only the test source code changes.

## The code under test

A header-only `Stack<T>` template with `push()`, `pop()`, `top()`, `empty()`, `size()`. The tests verify LIFO ordering, size tracking, and that empty-stack operations throw.

## Try it

```bash
cd 15_testing
make test           # builds and runs 5 tests
make                # builds just the app
./build/app         # top: 30, pop: 30, size: 2
make all            # builds both app and test binary
make clean
```

## Files

| File | Purpose |
|------|---------|
| `include/stack.hpp` | Header-only `Stack<T>` template |
| `src/main.cpp` | Demo app using the stack |
| `tests/test_stack.cpp` | 5 tests with custom assertion macros |
| `Makefile` | `all`, `test`, and `clean` targets |
