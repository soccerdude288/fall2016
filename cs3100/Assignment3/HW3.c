#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "rctimer.h"
typedef enum { false, true } bool;

int main(int argc, char *argv[]){
	start_timer();
	printf("Taylor Earl\n");
	printf("CS3100\n");

	//*********
	//USE THIS TO ENABLE PRINT STATEMENTS THROUGHOUT PROGRAM FOR DEBUGGING PURPOSES
	bool debug = true;
	//*********

	int numProc;
	int min, max;

	if(argc != 3){
		printf("You need to enter arguments.\n");
		exit(0);
	}

	if(*argv[1] == '1'){
		numProc = 1;
	}
	else if (*argv[1] == '4'){
		numProc = 4;
	}
	else {
		printf("You need to input either 1 or 4 processes.\n");
		exit(0);
	}
		
	const char * filename = argv[2];

	//FILE * ft= fopen(*argv[2], "rb");

	if(debug) printf("Now Opening File\n");

 	FILE * ft= fopen(filename, "rb") ;

	if(!ft){
		printf("Can't open file.\n");
		exit(0);
	}

	int pid = getpid();
    fseek (ft,0,SEEK_END); //go to end of file
    long size = ftell(ft); //what byte in file am I at?
    fseek (ft,0,SEEK_SET); //go to beginning of file
    int num = (int)size / (int)sizeof(int);
	if(debug) printf("size of the file: %li ,sizeof(int) = %i\n, the number of numbers = %i\n\n", size, (int) sizeof(int), num);
	int numbers[num];

	int k;
    for(k = 0; k < num; k++){
        int temp = 0;
        fread(&temp,sizeof(int),1,ft);
        numbers[k] = temp;
        //printf("%i: %i\t",pid,temp);
        usleep(500);
     }

     min = numbers[0];
     max = numbers[0];

  
  	if(debug){
  		printf("Below, the number inside the file will be printed.\n");
     	for(k=0; k < num; k++){
     		printf("%i\n", numbers[k]);
     	}
	}


    int cp[2];
    int childPipe[2];
    if(pipe(cp)<0){
    	printf("pipe didn't work.\n");
    	return 1;
    }
    if(pipe(childPipe)<0){
    	printf("pipe didn't work.\n");
    	return 1;
    }



	if(numProc == 1){
		if(debug) printf("Attempting Fork\n");
		int pid = fork();
		if(pid == 0){
			if(debug) printf("This is the child %d that has been created.\n", getpid());
			dup2(cp[0], 0); //make pipe read connect to stdin
			close(cp[1]);//close write of pipe

			if(debug) printf("This is the child %d. Pipes 1/2 been created.\n", getpid());
			
			close(childPipe[0]); //close read of pipe
			dup2(childPipe[1], 1); //make pipe write connect to stdout
			close(childPipe[1]);

			if(debug) printf("This is the child %d. Pipes have been created.\n", getpid());
			execl("minmax","minmax",(char*)NULL);
		}
		else{
			if(debug) printf("This is the parent %d that has been created.\n", getpid());
			
			close(cp[0]); //close read
			write(cp[1], &numbers, 4); //write to pipe
			close(cp[1]); //close pipe

			if(debug) printf("This is the parent %d. Pipes 1/2 been created.\n", getpid());

			close(childPipe[1]);
			//dup2(0,childPipe[0]);
			dup2(childPipe[0], 0);
			close(childPipe[0]);

			int chInt;
			int results[num];
			int i = 0;
			
			if(debug) printf("This is the parent %d. Pipes have been created.\n", getpid());

			
			while(read(0, &chInt, 4) == 4){
				results[i] = chInt;
				i++;
				if(chInt > max){
					max = chInt;
				}
				if(chInt < min){
					min = chInt;
				}
			}
			if(debug) printf("this is before the results and i=%d\n", i);
			for(;i > 0; i--){
				printf("test %d\n", results[i]);
			}
			printf("min = %d and max = %d\n", min, max);


		}
	}
	if(numProc == 4){
		int i = 0;
		if(debug) printf("this is 4 processes.\n");
		for(; i < numProc; i++){
			if(debug) printf("Attempting Fork\n");
			int pid = fork();
			if(pid == 0){
				if(debug) printf("This is the child %d that has been created.\n", getpid());
				dup2(cp[0], 0); //make pipe read connect to stdin
				close(cp[1]);//close write of pipe

				if(debug) printf("This is the child %d. Pipes 1/2 been created.\n", getpid());
				
				close(childPipe[0]); //close read of pipe
				dup2(childPipe[1], 1); //make pipe write connect to stdout
				close(childPipe[1]);

				if(debug) printf("This is the child %d. Pipes have been created.\n", getpid());
				execl("minmax","minmax",(char*)NULL);
			}
			else{
				if(debug) printf("This is the parent %d that has been created.\n", getpid());
				
				close(cp[0]); //close read
				write(cp[1], &numbers, 4); //write to pipe
				close(cp[1]); //close pipe

				if(debug) printf("This is the parent %d. Pipes 1/2 been created.\n", getpid());

				close(childPipe[1]);
				//dup2(0,childPipe[0]);
				dup2(childPipe[0], 0);
				close(childPipe[0]);

				int chInt;
				int results[num];
				int i = 0;
				
				if(debug) printf("This is the parent %d. Pipes have been created.\n", getpid());

				wait(NULL);
				while(read(0, &chInt, 4) == 4){
					results[i] = chInt;
					i++;
					if(chInt > max){
						max = chInt;
					}
					if(chInt < min){
						min = chInt;
					}
				}
				if(debug) printf("this is before the results and i=%d\n", i);
				for(;i > 0; i--){
					printf("%d\n", results[i]);
				}
			}
		}// end for
	printf("min = %d and max = %d\n", min, max);
	}

	fclose( ft ) ;
	end_timer();
	printf("Elapsed time: %s\n", get_elapsed_time());
	return 1;
};