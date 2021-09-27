.POSIX:

DEBUG = -g
XCFLAGS = $(CFLAGS) -Wall -Wextra -Wpedantic $(DEBUG)
CAIROCFLAGS = $$(pkgconf --cflags cairo)
CAIROLFLAGS = -lcairo

OBJS = \
	   image.o \
	   main.o \

all: cgol

%.o: %.c cgol.h
	$(CC) -c $(XCFLAGS) $(CAIROCFLAGS) $<

cgol: $(OBJS)
	$(CC) $(LDFLAGS) $(CAIROLFLAGS) $(OBJS) -o cgol

clean:
	rm -f $(OBJS) cgol

.PHONY: clean
