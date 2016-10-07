TARGET = main
SRCS   = $(wildcard *.c)
OBJS   = $(SRCS:.c=.o)
DEPS   = $(SRCS:.c=.d)

.PHONY: clean all

# if $CC is not set, use gcc as a sensible default
CC ?= gcc

# if $CFLAGS is not set, be very pedantic and compile
# as C11, that should catch some common errors, also
# fortify the source, which is a must for security.
CFLAGS ?= -Wall \
          -D_FORTIFY_SOURCE=2 \
          -Wextra -Wcast-align -Wcast-qual -Wpointer-arith \
          -Waggregate-return -Wunreachable-code -Wfloat-equal \
          -Wformat=2 -Wredundant-decls -Wundef \
          -Wdisabled-optimization -Wshadow -Wmissing-braces \
          -Wstrict-aliasing=2 -Wstrict-overflow=5 -Wconversion \
          -Wno-unused-parameter \
          -pedantic -std=c11

CFLAGS_DEBUG := -g3 \
                -O \
                -DDEBUG

CFLAGS_RELEASE := -O2 \
                  -march=native \
                  -mtune=native \
                  -ftree-vectorize

WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            -Wuninitialized -Wconversion -Wstrict-prototypes

CFLAGS += -MMD -MP 

all: $(TARGET)

$(TARGET): $(OBJS)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif
