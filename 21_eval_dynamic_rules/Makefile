# Lesson 21: $(eval) and Dynamic Rules
#
# $(eval) takes a string and interprets it as Makefile syntax at parse time.
# Combined with $(call) and $(foreach), it can generate rules from a list —
# eliminating boilerplate when you have many similar targets.
#
# The main pitfall: inside a define block passed to $(eval), you must
# double-escape $ for things that should expand at recipe time ($$@, $$^, etc.)
# while leaving single $ for things that should expand at eval time ($(1), $(CXX)).
#
# Note: $(eval) creates rules at parse time, so the first eval'd target would
# become the default goal. We set .DEFAULT_GOAL explicitly to keep `all` as
# the default regardless of rule order.

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -MMD -MP
AR       = ar
ARFLAGS  = rcs
BUILDDIR = build

# ── Shared library ──────────────────────────────────────
LIB_SRCS = src/config.cpp
LIB_OBJS = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(LIB_SRCS))
LIB      = $(BUILDDIR)/libconfig.a

# ── Programs to build (just a list!) ────────────────────
PROGRAMS = server client admin

.DEFAULT_GOAL = all

# ── The template: generates a link rule for each program ─
# $(1) is the program name, e.g. "server"
# Single $ → expands when $(eval) processes the template
# Double $$ → expands when Make runs the recipe
define make_program
$(1)_SRCS = src/$(1).cpp
$(1)_OBJS = $$(patsubst %.cpp,$$(BUILDDIR)/%.o,$$($(1)_SRCS))
$(1)_BIN  = $$(BUILDDIR)/$(1)

$$($(1)_BIN): $$($(1)_OBJS) $$(LIB)
	@mkdir -p $$(@D)
	$$(CXX) -o $$@ $$($(1)_OBJS) $$(LIB)
endef

# ── Stamp out rules for every program ───────────────────
$(foreach prog,$(PROGRAMS),$(eval $(call make_program,$(prog))))

# ── Collect all objects for dependency tracking ──────────
ALL_BINS = $(foreach prog,$(PROGRAMS),$($(prog)_BIN))
ALL_OBJS = $(LIB_OBJS) $(foreach prog,$(PROGRAMS),$($(prog)_OBJS))
DEPS     = $(ALL_OBJS:.o=.d)

.PHONY: all clean

all: $(ALL_BINS)

$(LIB): $(LIB_OBJS)
	@mkdir -p $(@D)
	$(AR) $(ARFLAGS) $@ $^

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR)

-include $(DEPS)
