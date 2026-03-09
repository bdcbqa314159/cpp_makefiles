# Lesson 13: Out-of-Source Builds
#
# All build artifacts (.o, .d, executable) go into build/
# instead of polluting the source tree. This keeps the
# project directory clean and makes `clean` trivial (rm -rf build/).
#
# Key technique: BUILDDIR prefix on all output paths.
# The pattern rule creates subdirectories as needed with
# @mkdir -p $(@D)
#   $(@D) = the directory part of the target path

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -MMD -MP
BUILDDIR = build
TARGET   = $(BUILDDIR)/app
SRCS     = src/main.cpp src/point.cpp
OBJS     = $(SRCS:%.cpp=$(BUILDDIR)/%.o)
DEPS     = $(OBJS:.o=.d)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) -o $@ $^

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR)

-include $(DEPS)
