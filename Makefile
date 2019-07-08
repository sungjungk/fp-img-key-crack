CFLAGS_GLIB = $(shell pkg-config --cflags --libs glib-2.0)

CFLAGS = -Wall -Werror -fopenmp -lm -g

all: fp-key-cracking

fp-key-cracking: fp-key-cracking.c
	gcc $< -o $@ $(CFLAGS) $(CFLAGS_GLIB)

clean:
	rm -f fp-key-cracking *.pgm

.PHONY: all clean
