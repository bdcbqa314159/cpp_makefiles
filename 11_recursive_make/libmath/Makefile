CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -MMD -MP
AR       = ar
ARFLAGS  = rcs
LIB      = libmath.a
SRCS     = ops.cpp
OBJS     = $(SRCS:.cpp=.o)
DEPS     = $(OBJS:.o=.d)

VPATH = src

.PHONY: all clean

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(LIB) $(OBJS) $(DEPS)

-include $(DEPS)
