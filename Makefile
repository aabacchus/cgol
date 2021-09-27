.POSIX:

-include config.mk

DEBUG = -g
XCFLAGS := $(CFLAGS) -Wall -Wextra -Wpedantic $(DEBUG) $(XXCFLAGS)
XLDFLAGS = $(LDFLAGS) $(XXLDFLAGS)

OBJS = \
	   image.o \
	   main.o \
	   rules.o \

all: cgol images

cgol: $(OBJS)
	$(CC) $(XLDFLAGS) $(OBJS) -o cgol

$(OBJS): $(OBJS:.o=.c) cgol.h

.c.o:
	$(CC) -c $(XCFLAGS) $<

images:
	mkdir -p images

out.webm: images
	ffmpeg -r 15 -i images/%04d.png $@

clean:
	rm -fr $(OBJS) cgol images/

.PHONY: clean
