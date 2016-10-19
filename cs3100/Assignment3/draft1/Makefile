all: HW3 write read

HW3: HW3.o
	gcc -Wall -Werror -ggdb HW3.o -o HW3
read: read.o
	gcc -Wall -Werror -ggdb read.o -o read
read.o: read.c
	gcc -Wall -Werror -ggdb -c read.c
HW3.o: HW3.c
	gcc -Wall -Werror -ggdb -c HW3.c

write: write.o
	gcc -Wall -Werror -ggdb write.o -o write

write.o: write.c
	gcc -Wall -Werror -ggdb -c write.c

clean:
	rm *o HW3
	rm *o write
	rm *o read
