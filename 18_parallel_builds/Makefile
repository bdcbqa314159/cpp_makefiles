# Lesson 18: Parallel Builds
#
# make -j N         — run up to N recipes simultaneously
# make -j$(nproc)   — use all CPU cores (Linux)
# make -j$(sysctl -n hw.ncpu)  — use all CPU cores (macOS)
# make -j           — unlimited parallelism (not recommended)
#
# How it works:
#   Make builds a dependency graph. Independent targets (like separate .o files)
#   can compile at the same time. Dependent targets wait for their prerequisites.
#
# Pitfalls:
#   - Race conditions happen when prerequisites are incomplete or missing.
#     If target A depends on target B but the Makefile doesn't declare it,
#     sequential make works by accident, but -j may build A before B is ready.
#   - Use order-only prerequisites (target: | dir) for directory creation.

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -MMD -MP
BUILDDIR = build

SRCS   = $(wildcard src/*.cpp)
OBJS   = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRCS))
DEPS   = $(OBJS:.o=.d)
TARGET = $(BUILDDIR)/app

.PHONY: all clean

all: $(TARGET)

# The link step depends on ALL object files — it waits for them all.
# With -j, all the .o files compile in parallel, then linking happens last.
$(TARGET): $(OBJS) | $(BUILDDIR)
	$(CXX) -o $@ $(OBJS)

# Each .o depends only on its own .cpp — these are independent.
# With -j4, up to 4 of these run simultaneously.
$(BUILDDIR)/%.o: %.cpp | $(BUILDDIR)/src
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Order-only prerequisites: the pipe (|) means "must exist, but don't
# check timestamps." Without this, creating the directory could trigger
# unnecessary rebuilds because mkdir updates the directory's mtime.
$(BUILDDIR):
	mkdir -p $@

$(BUILDDIR)/src:
	mkdir -p $@

clean:
	rm -rf $(BUILDDIR)

-include $(DEPS)
