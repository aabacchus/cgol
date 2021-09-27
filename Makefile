.POSIX:

DEBUG = -g
XCFLAGS = $(CFLAGS) -Wall -Wextra -Wpedantic $(DEBUG)
CAIROFLAGS = $$(pkgconf --cflags --libs cairo)

BINS = \
	   stroke

all: $(BINS)

$(BINS): $(BINS:=.c)
	$(CC) $(XCFLAGS) $(CAIROFLAGS) -o $@ $<

clean:
	rm -f $(BINS)

.PHONY: clean
