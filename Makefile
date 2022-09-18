CC=gcc
CFLAGS=-Wall -g
DESTDIR=/usr/bin

all: fcrypt

fcrypt: utils.o

clean:
	rm -f fcrypt
	rm -f *.o

install: all
	install fcrypt $(DESTDIR)

uninstall:
	rm -f $(DESTDIR)/fcrypt

valgrind: all
	valgrind ./fcrypt
