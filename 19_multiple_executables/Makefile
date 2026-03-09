# Lesson 19: Multiple Executables
#
# One Makefile that builds a shared library and two separate executables.
# Both executables link against the same library.
#
# Pattern:
#   1. Define each executable's sources separately
#   2. Build shared code into a static library
#   3. Link each executable against the library
#   4. `all` depends on every executable

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -MMD -MP
AR       = ar
ARFLAGS  = rcs
BUILDDIR = build

# ── Library ──────────────────────────────────────────────
LIB_SRCS = src/convert.cpp
LIB_OBJS = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(LIB_SRCS))
LIB      = $(BUILDDIR)/libconvert.a

# ── Executable 1: temp_tool ──────────────────────────────
TEMP_SRCS = src/temp_tool.cpp
TEMP_OBJS = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(TEMP_SRCS))
TEMP_BIN  = $(BUILDDIR)/temp_tool

# ── Executable 2: dist_tool ─────────────────────────────
DIST_SRCS = src/dist_tool.cpp
DIST_OBJS = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(DIST_SRCS))
DIST_BIN  = $(BUILDDIR)/dist_tool

# ── All objects (for dependency tracking) ────────────────
ALL_OBJS = $(LIB_OBJS) $(TEMP_OBJS) $(DIST_OBJS)
DEPS     = $(ALL_OBJS:.o=.d)

# ── Targets ──────────────────────────────────────────────
.PHONY: all clean

# `all` builds both executables
all: $(TEMP_BIN) $(DIST_BIN)

# Each executable links its own objects + the library
$(TEMP_BIN): $(TEMP_OBJS) $(LIB)
	@mkdir -p $(@D)
	$(CXX) -o $@ $(TEMP_OBJS) $(LIB)

$(DIST_BIN): $(DIST_OBJS) $(LIB)
	@mkdir -p $(@D)
	$(CXX) -o $@ $(DIST_OBJS) $(LIB)

# Static library from shared code
$(LIB): $(LIB_OBJS)
	@mkdir -p $(@D)
	$(AR) $(ARFLAGS) $@ $^

# Pattern rule for all .cpp → .o
$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR)

-include $(DEPS)
