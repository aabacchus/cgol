.POSIX:

-include config.mk

DEBUG = -g
XCFLAGS := $(CFLAGS) -Wall -Wextra -Wpedantic $(DEBUG) $(XXCFLAGS) -D_XOPEN_SOURCE=600
XLDFLAGS = $(LDFLAGS) $(XXLDFLAGS)

OBJS = \
	   main.o \
	   rules.o \
	   ascii.o \
#	   image.o \

all: cgol images

cgol: $(OBJS)
	$(CC) $(XLDFLAGS) $(OBJS) -o cgol

$(OBJS): cgol.h

.c.o:
	$(CC) -c $(XCFLAGS) $<

images:
	mkdir -p images

out.webm: images
	ffmpeg -r 15 -i images/%06d.png $@

clean:
	rm -fr $(OBJS) cgol images/

.PHONY: clean
