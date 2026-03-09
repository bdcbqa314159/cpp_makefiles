# Lesson 08: Multiple Targets
#
# A Makefile can have multiple targets. The first target is
# the default (what `make` with no arguments builds).
#
# .PHONY declares targets that aren't files. Without it,
# if a file named "clean" existed, `make clean` would say
# "clean is up to date" and do nothing.
#
# Common conventions:
#   all     — build everything (default target)
#   clean   — remove build artifacts
#   rebuild — clean + build from scratch

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -MMD -MP
TARGET   = app
SRCS     = main.cpp logger.cpp
OBJS     = $(SRCS:.cpp=.o)
DEPS     = $(OBJS:.o=.d)

VPATH = src

.PHONY: all clean rebuild

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

rebuild: clean all

-include $(DEPS)
