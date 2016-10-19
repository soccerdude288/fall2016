all: stack

stack: main.o stack.o
	gcc main.o stack.o -o Assignment1

main.o: main.c
	gcc -c main.c

stack.o: stack.c
	gcc -c stack.c

clean:
	rm *o Assignment1
