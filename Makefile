CC=gcc
CFLAGS=-g -W -Wall -std=c11
LDFLAGS=
EXEC=snc

all: $(EXEC)

snc: snc.o main.o
	$(CC) -o snc snc.o main.o -lm $(LDFLAGS)

snc.o: SNC.c
	$(CC) -o snc.o -g -c SNC.c $(CFLAGS)

main.o: main.c SNC.h
	$(CC) -o main.o -g -c main.c -lm $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)