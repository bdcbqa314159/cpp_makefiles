# Lesson 17: Functions & Auto-Discovery
#
# Key functions:
#   $(wildcard pattern)          — expand glob, return matching files
#   $(patsubst from,to,text)     — pattern substitution
#   $(filter pattern,text)       — keep only matching words
#   $(filter-out pattern,text)   — remove matching words
#   $(foreach var,list,body)     — loop over a list
#   $(call name,args...)         — invoke a user-defined function
#   $(sort list)                 — sort and deduplicate
#   $(words list)                — count words in list
#
# The big idea: auto-discover source files instead of listing them manually.
# Add a new .cpp to src/ and it's automatically compiled — no Makefile edits.

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -MMD -MP
BUILDDIR = build

# ── Auto-discovery ───────────────────────────────────────
# $(wildcard) finds all matching files — no manual list needed
SRCS = $(wildcard src/*.cpp)

# $(filter-out) removes main.cpp so we can link it separately if needed
LIB_SRCS = $(filter-out src/main.cpp, $(SRCS))

# $(patsubst) is the full form of substitution references
# These two lines are equivalent:
#   OBJS = $(SRCS:%.cpp=$(BUILDDIR)/%.o)
#   OBJS = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRCS))
OBJS = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRCS))

DEPS   = $(OBJS:.o=.d)
TARGET = $(BUILDDIR)/app

# ── User-defined function with $(call) ───────────────────
# $(1) is the first argument passed to the function
announce = @echo "── $(1) ──"

# ── Targets ──────────────────────────────────────────────
.PHONY: all clean info

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(call announce,Linking $@)
	$(CXX) -o $@ $^

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR)

# ── Info target: show what the functions resolved to ─────
info:
	@echo "SRCS     = $(SRCS)"
	@echo "LIB_SRCS = $(LIB_SRCS)"
	@echo "OBJS     = $(OBJS)"
	@echo ""
	@echo "File count: $(words $(SRCS)) source files"
	@echo "Sorted:     $(sort $(SRCS))"

-include $(DEPS)
