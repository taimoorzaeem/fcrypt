CC=gcc
CFLAGS=-Wall -g

all: main.o file_encrypt_decrypt.o
	$(CC) $(CFLAGS) main.o file_encrypt_decrypt.o -o file_encrypt_decrypt

clean:
	rm -f *.o
