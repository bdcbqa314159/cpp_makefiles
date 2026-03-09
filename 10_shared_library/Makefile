# Lesson 10: Shared Library
#
# A shared library (.so on Linux, .dylib on macOS) is loaded
# at runtime. The executable doesn't contain the library code —
# it contains a reference to it.
#
# Key flags:
#   -fPIC    Position Independent Code — required for shared libs
#   -shared  tell the linker to produce a shared library
#   -rpath   embed the library search path in the executable
#            so it finds the .dylib/.so at runtime without
#            setting LD_LIBRARY_PATH / DYLD_LIBRARY_PATH
#
# On macOS the extension is .dylib, on Linux it's .so.
# We detect the platform with uname.

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -MMD -MP -fPIC
TARGET   = app

UNAME := $(shell uname)
ifeq ($(UNAME),Darwin)
    LIB = libstrutil.dylib
    RPATH_FLAG = -Wl,-rpath,@executable_path
else
    LIB = libstrutil.so
    RPATH_FLAG = -Wl,-rpath,'$$ORIGIN'
endif

LIB_SRCS = strutil.cpp
LIB_OBJS = $(LIB_SRCS:.cpp=.o)
APP_SRCS = main.cpp
APP_OBJS = $(APP_SRCS:.cpp=.o)
DEPS     = $(LIB_OBJS:.o=.d) $(APP_OBJS:.o=.d)

VPATH = src

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(APP_OBJS) $(LIB)
	$(CXX) -o $@ $(APP_OBJS) -L. -lstrutil $(RPATH_FLAG)

$(LIB): $(LIB_OBJS)
	$(CXX) -shared -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(LIB) $(LIB_OBJS) $(APP_OBJS) $(DEPS)

-include $(DEPS)
