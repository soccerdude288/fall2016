all: HW3 minmax

minmax: minmax.o
	gcc minmax.o -o minmax

HW3: HW3.o
	gcc HW3.o -o HW3

HW3.o: HW3.c
	gcc -c HW3.c

minmax.o: minmax.c
	gcc -c minmax.c

clean:
	rm *o HW3
	rm *o minmax