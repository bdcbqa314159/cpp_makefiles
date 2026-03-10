# Lesson 23: pkg-config and Third-Party Libraries
#
# pkg-config provides the correct compiler and linker flags for installed
# libraries. Instead of hardcoding -I and -L paths, you ask pkg-config:
#
#   pkg-config --cflags zlib   →  (include paths, if any)
#   pkg-config --libs zlib     →  -lz
#
# This is how real Makefiles integrate with OpenSSL, zlib, SDL2, libpng, etc.

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -MMD -MP
LDFLAGS  =
BUILDDIR = build

# ── pkg-config integration ──────────────────────────────
# Try pkg-config first; fall back to plain -lz if unavailable
HAVE_PKGCONFIG := $(shell pkg-config --exists zlib 2>/dev/null && echo yes)

ifeq ($(HAVE_PKGCONFIG),yes)
    ZLIB_CFLAGS := $(shell pkg-config --cflags zlib)
    ZLIB_LIBS   := $(shell pkg-config --libs zlib)
else
    # Fallback: zlib is commonly available without pkg-config
    $(info pkg-config not found or zlib.pc missing — using fallback flags)
    ZLIB_CFLAGS :=
    ZLIB_LIBS   := -lz
endif

CXXFLAGS += $(ZLIB_CFLAGS)
LDFLAGS  += $(ZLIB_LIBS)

SRCS   = $(wildcard src/*.cpp)
OBJS   = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRCS))
DEPS   = $(OBJS:.o=.d)
TARGET = $(BUILDDIR)/app

.PHONY: all clean check-deps

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR)

# ── Dependency check ────────────────────────────────────
check-deps:
	@echo "Checking for zlib..."
	@if pkg-config --exists zlib 2>/dev/null; then \
		echo "  zlib found via pkg-config:"; \
		echo "    cflags: $$(pkg-config --cflags zlib)"; \
		echo "    libs:   $$(pkg-config --libs zlib)"; \
		echo "    version: $$(pkg-config --modversion zlib)"; \
	else \
		echo "  pkg-config: zlib.pc not found"; \
		echo "  Trying fallback: checking for -lz..."; \
		echo 'int main(){}' | $(CXX) -x c++ - -lz -o /dev/null 2>/dev/null \
			&& echo "  -lz works (zlib available without pkg-config)" \
			|| echo "  ERROR: zlib not found — install zlib development package"; \
	fi

-include $(DEPS)
