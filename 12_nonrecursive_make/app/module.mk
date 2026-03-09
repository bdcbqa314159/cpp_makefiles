# Fragment included by the top-level Makefile.

APP_SRCS = app/src/main.cpp
APP_OBJS = $(APP_SRCS:.cpp=.o)
APP_BIN  = app/app

$(APP_BIN): $(APP_OBJS) $(LIBFMT_LIB)
	$(CXX) -o $@ $(APP_OBJS) $(LIBFMT_LIB)
