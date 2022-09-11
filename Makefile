CC=gcc
CFLAGS=-Wall -g
DESTDIR=/usr/bin

all: fcrypt

fcrypt: utils.o

clean:
	rm -f *.o

install: all
	install fcrypt $(DESTDIR)

valgrind: all
	valgrind ./fcrypt
