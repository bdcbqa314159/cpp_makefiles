CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -I../libmath/include -MMD -MP
TARGET   = app
SRCS     = main.cpp
OBJS     = $(SRCS:.cpp=.o)
DEPS     = $(OBJS:.o=.d)

VPATH = src

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ -L../libmath -lmath

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)
