/*  Ted Cowan, CS3210 Lab 3 Skeleton File */

/*  usage:  zap <filename> <offset> <textstring> */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
	void *buf;
	int inputFile;
	struct stat fileStat;
	int offset, len;
	
	offset = atoi(argv[2]);
	len = strlen(argv[3]);

	char insertString[] = argv[3];	

	if (argc != 4) {
		printf("Usage: zap <filename> <offset> <textstring>\n");
		return 1;
	}

	inputFile = open(argv[1],O_RDWR); 	
	if (inputFile<0) {
		perror("Cannot open input file");
		return 1;
	}
	if (fstat(inputFile, &fileStat)) {
		perror("fstat() failed");
		return 1;
	}
	/*  Map the file into memory */
	
		/*  YOUR MMAP() goes here */
	
	f = (char *) mmap (*buf, len, PROT_READ|PROT_WRITE, MAP_PRIVATE, inputFile, 0);
	if(f == MAP_FAILED){
		perror('mmap()');
	}

	/*  Zap the file contents with my name */

    /*
	for(int i=0; i < len; i++){
		f[i] = insertString[i];
	}
    */
		/*  YOUR MEMCPY() GOES HERE */

    f += offset;
    memcpy(f, *buf, len);


	/*  Clean up */

		/*  YOUR MSYNC() GOES HERE */
    if(msync(*buf, len, MS_SYNC) < 0){
        perror("msync failed with error:");
    }
	munmap(buf, fileStat.st_size);
	close(inputFile);

	return 0;
}

