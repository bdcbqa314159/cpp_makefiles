# Lesson 14: Conditional Logic
#
# Make supports conditionals:
#   ifeq ($(VAR),value)   — string equality
#   ifneq                 — string inequality
#   ifdef / ifndef        — variable defined or not
#
# Common uses:
#   - Debug vs release builds (optimization, symbols, defines)
#   - Platform detection (different flags for Linux vs macOS)
#   - Optional features via user-defined variables
#
# Usage:
#   make                  → debug build (default)
#   make BUILD=release    → release build
#   make BUILD=release VERSION=1.2.3

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -MMD -MP
BUILDDIR = build
TARGET   = $(BUILDDIR)/app

# ── Build mode ────────────────────────────────────────────
BUILD ?= debug

ifeq ($(BUILD),release)
    CXXFLAGS += -O2 -DNDEBUG
    BUILDDIR  = build/release
else ifeq ($(BUILD),debug)
    CXXFLAGS += -g -O0 -fsanitize=address
    LDFLAGS  += -fsanitize=address
    BUILDDIR  = build/debug
else
    $(error Unknown BUILD mode: $(BUILD). Use 'debug' or 'release')
endif

# ── Optional version define ───────────────────────────────
ifdef VERSION
    CXXFLAGS += -DAPP_VERSION=$(VERSION)
endif

# ── Platform detection ────────────────────────────────────
UNAME := $(shell uname)
ifeq ($(UNAME),Linux)
    CXXFLAGS += -pthread
endif

# ── Sources ───────────────────────────────────────────────
SRCS   = src/main.cpp src/app.cpp
OBJS   = $(SRCS:%.cpp=$(BUILDDIR)/%.o)
DEPS   = $(OBJS:.o=.d)
TARGET = $(BUILDDIR)/app

.PHONY: all clean info

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) -o $@ $^

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf build

# Print resolved configuration (handy for debugging Makefiles)
info:
	@echo "BUILD    = $(BUILD)"
	@echo "CXX      = $(CXX)"
	@echo "CXXFLAGS = $(CXXFLAGS)"
	@echo "LDFLAGS  = $(LDFLAGS)"
	@echo "TARGET   = $(TARGET)"
	@echo "UNAME    = $(UNAME)"

-include $(DEPS)
