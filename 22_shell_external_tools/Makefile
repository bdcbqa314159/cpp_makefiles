# Lesson 22: $(shell) and External Tools
#
# $(shell cmd) runs a command during Makefile parsing and captures stdout.
# Use it to embed git metadata, detect platforms, and check for tools.
#
# IMPORTANT: Always use := (immediate assignment) with $(shell).
# With = (deferred), the shell command re-runs every time the variable
# is referenced — a serious performance hit.

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -MMD -MP
BUILDDIR = build

# ── External tool integration ───────────────────────────
# := means "expand now" — the shell command runs once during parsing
GIT_SHA    := $(shell git rev-parse --short HEAD 2>/dev/null || echo unknown)
BUILD_DATE := $(shell date +%Y-%m-%d)
BUILD_HOST := $(shell hostname 2>/dev/null || echo unknown)
NPROC      := $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 1)

# Pass build metadata to C++ as preprocessor defines
CXXFLAGS += -DGIT_SHA=\"$(GIT_SHA)\" \
            -DBUILD_DATE=\"$(BUILD_DATE)\" \
            -DBUILD_HOST=\"$(BUILD_HOST)\"

SRCS   = $(wildcard src/*.cpp)
OBJS   = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRCS))
DEPS   = $(OBJS:.o=.d)
TARGET = $(BUILDDIR)/app

.PHONY: all clean info

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) -o $@ $^

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR)

# ── Info target: show what $(shell) captured ─────────────
info:
	@echo "GIT_SHA    = $(GIT_SHA)"
	@echo "BUILD_DATE = $(BUILD_DATE)"
	@echo "BUILD_HOST = $(BUILD_HOST)"
	@echo "NPROC      = $(NPROC)"

# ── Force rebuild of build_info.o when git SHA changes ──
# The git SHA can change without any source file changing, so Make's
# timestamp check won't trigger a rebuild. Adding FORCE as a
# prerequisite makes this single object always recompile (it's cheap).
$(BUILDDIR)/src/build_info.o: FORCE
FORCE:

-include $(DEPS)
