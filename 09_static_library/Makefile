# Lesson 09: Static Library
#
# A static library (.a) is an archive of .o files.
# The linker copies the needed code into the executable.
# The .a file is not needed at runtime.
#
# ar rcs libmathlib.a mathlib.o
#   ar  — the archiver tool
#   r   — replace files in the archive
#   c   — create if it doesn't exist
#   s   — write an index (ranlib equivalent)
#
# Linking: put -L. (library search path) and -lmathlib
# after the source/object files. The linker processes
# arguments left-to-right — the library must come after
# the code that references it.

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -MMD -MP
AR       = ar
ARFLAGS  = rcs
TARGET   = app
LIB      = libmathlib.a
LIB_SRCS = mathlib.cpp
LIB_OBJS = $(LIB_SRCS:.cpp=.o)
APP_SRCS = main.cpp
APP_OBJS = $(APP_SRCS:.cpp=.o)
DEPS     = $(LIB_OBJS:.o=.d) $(APP_OBJS:.o=.d)

VPATH = src

.PHONY: all clean

all: $(TARGET)

# Link the app against the static library
$(TARGET): $(APP_OBJS) $(LIB)
	$(CXX) -o $@ $(APP_OBJS) -L. -lmathlib

# Build the static library from its object files
$(LIB): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(LIB) $(LIB_OBJS) $(APP_OBJS) $(DEPS)

-include $(DEPS)
