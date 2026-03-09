# Lesson 03: Variables
#
# Instead of hardcoding g++, flags, and file lists everywhere,
# we use variables. Change the compiler or flags in one place.
#
# Convention:
#   CXX      — C++ compiler
#   CXXFLAGS — compile flags (warnings, standard, optimization)
#   LDFLAGS  — linker flags (library paths, etc.)
#   TARGET   — the executable name
#   SRCS     — source files
#   OBJS     — object files (derived from SRCS)

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra
LDFLAGS  =
TARGET   = main
SRCS     = main.cpp greet.cpp
OBJS     = main.o greet.o

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

main.o: main.cpp greet.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

greet.o: greet.cpp greet.hpp
	$(CXX) $(CXXFLAGS) -c greet.cpp

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
