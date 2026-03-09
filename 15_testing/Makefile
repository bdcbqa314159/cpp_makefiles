# Lesson 15: Testing
#
# The `test` target compiles and runs the test executable.
# If any test fails (non-zero exit), Make reports an error.
#
# Pattern:
#   make        → build the app
#   make test   → build and run tests
#   make all    → build both app and tests (but don't run)
#
# The test binary links against the same library code as
# the app (here it's header-only, so just includes).

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -MMD -MP
BUILDDIR = build

APP_TARGET  = $(BUILDDIR)/app
TEST_TARGET = $(BUILDDIR)/test_stack

APP_SRCS  = src/main.cpp
TEST_SRCS = tests/test_stack.cpp

APP_OBJS  = $(APP_SRCS:%.cpp=$(BUILDDIR)/%.o)
TEST_OBJS = $(TEST_SRCS:%.cpp=$(BUILDDIR)/%.o)
ALL_DEPS  = $(APP_OBJS:.o=.d) $(TEST_OBJS:.o=.d)

.PHONY: all clean test

all: $(APP_TARGET) $(TEST_TARGET)

$(APP_TARGET): $(APP_OBJS)
	@mkdir -p $(@D)
	$(CXX) -o $@ $^

$(TEST_TARGET): $(TEST_OBJS)
	@mkdir -p $(@D)
	$(CXX) -o $@ $^

# Build and run tests
test: $(TEST_TARGET)
	@echo "Running tests..."
	@./$(TEST_TARGET)

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR)

-include $(ALL_DEPS)
