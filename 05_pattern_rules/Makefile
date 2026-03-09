# Lesson 05: Pattern Rules
#
# Instead of writing a separate rule for each .o file,
# a pattern rule handles all of them:
#
#   %.o: %.cpp
#       $(CXX) $(CXXFLAGS) -c -o $@ $<
#
# The % is a wildcard (the "stem"). When Make needs main.o,
# it matches main against %, looks for main.cpp, and runs
# the recipe with $@ = main.o and $< = main.cpp.
#
# Now adding a new .cpp file only requires adding it to SRCS.

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra
TARGET   = main
SRCS     = main.cpp vec.cpp
OBJS     = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

# One rule to compile them all
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
