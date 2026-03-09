# Lesson 07: Automatic Header Dependencies
#
# Problem: in lesson 06, header dependencies were manual.
# If you change config.hpp but the Makefile doesn't list it
# as a prerequisite, Make won't recompile. Bugs ensue.
#
# Solution: the compiler can generate dependency files (.d)
# that list every header a .cpp includes.
#
#   -MMD  generates a .d file alongside the .o file
#   -MP   adds phony targets for each header (avoids errors
#         when headers are deleted/renamed)
#
# The -include directive loads all .d files silently.
# On first build, no .d files exist — that's fine, the
# pattern rule compiles everything anyway.

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -MMD -MP
TARGET   = main
SRCS     = main.cpp store.cpp
OBJS     = $(SRCS:.cpp=.o)
DEPS     = $(OBJS:.o=.d)

VPATH = src

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

# Pull in auto-generated dependency rules
-include $(DEPS)
