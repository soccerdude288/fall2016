#Taylor Earl
#Lab 9
#10/17/2016

CFLAGS = -Wall -Werror -ggdb
CC = gcc

all: addr

addr: addr.o screen.o db.o
	$(CC) addr.o screen.o db.o -o addr
addr.o: addr.c addr.h
	$(CC) $(CFLAGS) -c addr.c addr.h
clean:
	-rm *o addr	
