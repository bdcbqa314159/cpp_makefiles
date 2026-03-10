# Lesson 24: install Target
#
# The `install` target copies built artifacts to system directories.
# Conventions:
#   PREFIX  -- base directory (default: /usr/local)
#   DESTDIR -- staging root for package builders (prepended to all paths)
#   BINDIR  -- where executables go ($(PREFIX)/bin)
#   LIBDIR  -- where libraries go ($(PREFIX)/lib)
#   INCDIR  -- where headers go ($(PREFIX)/include)
#
# The `install` command (not `cp`) is used because it:
#   - Sets file permissions in one step
#   - Creates directories with -d
#   - Is the standard tool for this job on Unix

CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Iinclude -MMD -MP
AR       = ar
ARFLAGS  = rcs
BUILDDIR = build

# -- Install directories -----------------------------------------
PREFIX  ?= /usr/local
BINDIR   = $(PREFIX)/bin
LIBDIR   = $(PREFIX)/lib
INCDIR   = $(PREFIX)/include/greetlib

# -- Library -----------------------------------------------------
LIB_SRCS = src/greet.cpp
LIB_OBJS = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(LIB_SRCS))
LIB      = $(BUILDDIR)/libgreet.a

# -- Executable --------------------------------------------------
APP_SRCS = src/main.cpp
APP_OBJS = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(APP_SRCS))
TARGET   = $(BUILDDIR)/greeter

ALL_OBJS = $(LIB_OBJS) $(APP_OBJS)
DEPS     = $(ALL_OBJS:.o=.d)

.PHONY: all clean install uninstall debug

all: $(TARGET)

$(TARGET): $(APP_OBJS) $(LIB)
	@mkdir -p $(@D)
	$(CXX) -o $@ $(APP_OBJS) $(LIB)

$(LIB): $(LIB_OBJS)
	@mkdir -p $(@D)
	$(AR) $(ARFLAGS) $@ $^

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR)

# -- Install target ----------------------------------------------
# DESTDIR is prepended for staged installs (e.g., packaging)
install: $(TARGET) $(LIB)
	install -d $(DESTDIR)$(BINDIR)
	install -m 755 $(TARGET) $(DESTDIR)$(BINDIR)
	install -d $(DESTDIR)$(LIBDIR)
	install -m 644 $(LIB) $(DESTDIR)$(LIBDIR)
	install -d $(DESTDIR)$(INCDIR)
	install -m 644 include/greet.hpp $(DESTDIR)$(INCDIR)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(notdir $(TARGET))
	rm -f $(DESTDIR)$(LIBDIR)/$(notdir $(LIB))
	rm -f $(DESTDIR)$(INCDIR)/greet.hpp
	-rmdir $(DESTDIR)$(INCDIR) 2>/dev/null || true

# -- File manipulation functions ---------------------------------
# Make provides functions to dissect paths -- useful in install rules
debug:
	@echo "=== Path Functions ==="
	@echo "TARGET          = $(TARGET)"
	@echo "\$$(notdir ...)  = $(notdir $(TARGET))"
	@echo "\$$(dir ...)     = $(dir $(TARGET))"
	@echo "\$$(basename ...) = $(basename $(TARGET))"
	@echo "\$$(suffix ...)  = $(suffix $(LIB))"
	@echo ""
	@echo "=== Install Paths ==="
	@echo "PREFIX  = $(PREFIX)"
	@echo "DESTDIR = $(DESTDIR)"
	@echo "BINDIR  = $(DESTDIR)$(BINDIR)"
	@echo "LIBDIR  = $(DESTDIR)$(LIBDIR)"
	@echo "INCDIR  = $(DESTDIR)$(INCDIR)"

-include $(DEPS)
