# Lesson 04: Automatic Variables
#
# Make provides special variables inside recipes:
#   $@  — the target filename
#   $<  — the first prerequisite
#   $^  — all prerequisites (space-separated, deduplicated)
#   $*  — the stem matched by a pattern rule (lesson 05)
#
# These eliminate repetition: the recipe doesn't hardcode filenames.

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra
TARGET   = main
OBJS     = main.o calc.o

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

# $@ is main.o, $< is main.cpp (first prerequisite)
main.o: main.cpp calc.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

calc.o: calc.cpp calc.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
