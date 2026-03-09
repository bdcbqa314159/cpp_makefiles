# Lesson 02: Targets & Dependencies
#
# The build happens in two stages:
#   1. Compile each .cpp into a .o (object file)
#   2. Link all .o files into the executable
#
# If you change only math.cpp, Make only recompiles math.o
# and re-links. main.o is untouched.

main: main.o math.o
	g++ -std=c++20 -o main main.o math.o

main.o: main.cpp math.hpp
	g++ -std=c++20 -Wall -Wextra -c main.cpp

math.o: math.cpp math.hpp
	g++ -std=c++20 -Wall -Wextra -c math.cpp
