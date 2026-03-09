# Fragment included by the top-level Makefile.
# Defines this module's objects and dependency on headers.

LIBFMT_SRCS = libfmt/src/fmt.cpp
LIBFMT_OBJS = $(LIBFMT_SRCS:.cpp=.o)
LIBFMT_LIB  = libfmt/libfmt.a

$(LIBFMT_LIB): $(LIBFMT_OBJS)
	$(AR) $(ARFLAGS) $@ $^
