# Lesson 06: Separate src/ and include/ Directories
#
# Real projects don't put everything in one folder.
# Headers go in include/, source files in src/.
#
# Two key mechanisms:
#   -Iinclude       tells the compiler where to find headers
#   VPATH = src     tells Make where to find .cpp files
#                   when a pattern rule needs them

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude
TARGET   = main
SRCS     = main.cpp counter.cpp
OBJS     = $(SRCS:.cpp=.o)

# Tell Make to search src/ for .cpp files
VPATH = src

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
