#Taylor Earl
#Lab 9

CFLAGS = -Wall -Werror -ggdb
CC = gcc

all: addr

addr: addr.o screen.o db.o
	$(CC) $(CFLAGS) addr.o screen.o db.o -o addr
addr.o: addr.c addr.h
	$(CC) $(CFLAGS) -c addr.c addr.h