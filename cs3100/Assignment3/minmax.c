#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


int main(int arc, char *argv[]){
	
	int ch;
	int max, min;
	int test = 1;
	while(read(0, &ch, 4) == 4){
		int num;
		//num = (int)ch;
		num = (int)ch;
		if(test = 1){
			max = num;
			min = num;
			test = 2;
		}

		if(num > max){
			max = num;
		}
		if(num < min){
			min = num;
		}
		
	}
	//printf("%d%d\n", min, max);
	//printf("We made it!!!");
	int minMaxArray[] = {min, max};
	//fprintf(1, "Min is %d, Max is %d\n", min, max);
	write(1, &minMaxArray, sizeof(int));

	return 1;
}
