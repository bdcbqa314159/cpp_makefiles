# Lesson 12: Non-Recursive Make
#
# Instead of each subdirectory having its own Makefile invoked
# via $(MAKE) -C, a single top-level Makefile includes fragments
# (module.mk) from each subdirectory.
#
# Advantages over recursive Make:
#   - Make sees ALL dependencies in one graph
#   - Parallel builds (-j) work correctly across modules
#   - No ordering issues (Make resolves them from the graph)
#
# Each module.mk defines its own SRCS, OBJS, and targets
# using full paths relative to the project root.

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Ilibfmt/include -MMD -MP
AR       = ar
ARFLAGS  = rcs

# Declare default target BEFORE includes, so module.mk
# targets don't accidentally become the default.
.PHONY: all clean

all:

# Include module fragments
include libfmt/module.mk
include app/module.mk

# Now wire the default target (all variables are defined)
all: $(APP_BIN)

# Collect all objects and deps
ALL_OBJS = $(LIBFMT_OBJS) $(APP_OBJS)
ALL_DEPS = $(ALL_OBJS:.o=.d)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(APP_BIN) $(LIBFMT_LIB) $(ALL_OBJS) $(ALL_DEPS)

-include $(ALL_DEPS)
