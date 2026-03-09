# Lesson 16: Make vs CMake — the Makefile version
#
# This is a "production-quality" Makefile that combines
# everything from lessons 01–15:
#   - Variables, pattern rules, automatic variables
#   - Separate src/include
#   - Auto header dependencies (-MMD -MP)
#   - Out-of-source builds
#   - Debug/release via BUILD=
#   - Test target
#   - .PHONY, clean
#
# Compare this with CMakeLists.txt in the same directory.
# CMake generates a Makefile (or Ninja file) automatically
# from a higher-level description. Everything you see below
# is what CMake does for you behind the scenes.

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -MMD -MP

BUILD ?= debug
ifeq ($(BUILD),release)
    CXXFLAGS += -O2 -DNDEBUG
    BUILDDIR  = build/release
else
    CXXFLAGS += -g -O0
    BUILDDIR  = build/debug
endif

LIB_SRCS    = src/matrix.cpp
APP_SRCS    = src/main.cpp
TEST_SRCS   = tests/test_matrix.cpp

LIB_OBJS    = $(LIB_SRCS:%.cpp=$(BUILDDIR)/%.o)
APP_OBJS    = $(APP_SRCS:%.cpp=$(BUILDDIR)/%.o)
TEST_OBJS   = $(TEST_SRCS:%.cpp=$(BUILDDIR)/%.o)
ALL_DEPS    = $(LIB_OBJS:.o=.d) $(APP_OBJS:.o=.d) $(TEST_OBJS:.o=.d)

APP_TARGET  = $(BUILDDIR)/app
TEST_TARGET = $(BUILDDIR)/test_matrix
LIB         = $(BUILDDIR)/libmatrix.a

AR      = ar
ARFLAGS = rcs

.PHONY: all clean test

all: $(APP_TARGET)

$(LIB): $(LIB_OBJS)
	@mkdir -p $(@D)
	$(AR) $(ARFLAGS) $@ $^

$(APP_TARGET): $(APP_OBJS) $(LIB)
	@mkdir -p $(@D)
	$(CXX) -o $@ $(APP_OBJS) $(LIB)

$(TEST_TARGET): $(TEST_OBJS) $(LIB)
	@mkdir -p $(@D)
	$(CXX) -o $@ $(TEST_OBJS) $(LIB)

test: $(TEST_TARGET)
	@echo "Running tests..."
	@./$(TEST_TARGET)

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf build

-include $(ALL_DEPS)
