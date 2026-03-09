# Lesson 20: Debugging Makefiles
#
# When a Makefile doesn't do what you expect, these tools help:
#
#   make -n          dry run: print commands without executing them
#   make -p          print the entire database of rules and variables
#   make -d          trace: print detailed decision-making info
#   make --trace     print each target as it's rebuilt (less verbose than -d)
#   $(info ...)      print a message during Makefile parsing (no prefix)
#   $(warning ...)   print a message with file:line location
#   $(error ...)     print a message and abort
#
# These are NOT compile flags — they're Make's own diagnostic tools.

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -MMD -MP
BUILDDIR = build

SRCS   = $(wildcard src/*.cpp)
OBJS   = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRCS))
DEPS   = $(OBJS:.o=.d)
TARGET = $(BUILDDIR)/app

# ── Debugging with $(info) and $(warning) ────────────────
# These run during Makefile parsing (before any recipes execute).
# Uncomment to see them in action:
#
# $(info [debug] SRCS = $(SRCS))
# $(info [debug] OBJS = $(OBJS))
# $(warning This is a warning with file:line info)

# ── Guard: require at least one source file ──────────────
ifeq ($(SRCS),)
    $(error No source files found in src/ — check your directory)
endif

.PHONY: all clean debug

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) -o $@ $^

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR)

# ── Debug target: print all resolved variables ───────────
# A convenient alternative to make -p (which dumps everything)
debug:
	@echo "=== Makefile Debug ==="
	@echo "CXX      = $(CXX)"
	@echo "CXXFLAGS = $(CXXFLAGS)"
	@echo "BUILDDIR = $(BUILDDIR)"
	@echo "SRCS     = $(SRCS)"
	@echo "OBJS     = $(OBJS)"
	@echo "DEPS     = $(DEPS)"
	@echo "TARGET   = $(TARGET)"
	@echo ""
	@echo "=== Make Version ==="
	@$(MAKE) --version | head -1
	@echo ""
	@echo "=== Try these ==="
	@echo "  make -n          # dry run"
	@echo "  make -n all      # dry run for 'all' target"
	@echo "  make -p | less   # full database dump"
	@echo "  make --trace     # trace rebuilds"

-include $(DEPS)
