# Lesson 11: Recursive Make
#
# Each subdirectory has its own Makefile. The top-level
# Makefile coordinates them with $(MAKE) -C <dir>.
#
# $(MAKE) instead of `make` ensures the same Make binary
# and flags (like -j for parallel builds) propagate down.
#
# Order matters: libmath must be built before app.
# This is the traditional approach. It works, but has
# limitations — Make can't see dependencies across
# subdirectories, so parallel builds may miss ordering.
# Lesson 12 shows the alternative.

.PHONY: all clean

all:
	$(MAKE) -C libmath
	$(MAKE) -C app

clean:
	$(MAKE) -C libmath clean
	$(MAKE) -C app clean
