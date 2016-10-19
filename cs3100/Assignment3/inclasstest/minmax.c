#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>

int main(int argc, char *argv[]) { 
	int i;
	int results[100];

	while(read(0, &chInt, 4) == 4){
		results[i] = chInt;
		i++;
	}
	printf("this is before the results and i=%d\n", i);
	for(;i > 0; i--){
		printf("%d\n", results[i]);
	}
	





	printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer); 
	exit(EXIT_SUCCESS);
}
