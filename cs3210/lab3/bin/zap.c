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

	//const char *insertString[len] = argv[3];
    //*insertString = argv[3];

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

	buf = (char *) mmap (NULL, len, PROT_WRITE, MAP_SHARED, inputFile, 0);
	if(buf == MAP_FAILED){
		perror("mmap()");
        return 1;
	}

	/*  Zap the file contents with my name */

    /*  YOUR MEMCPY() GOES HERE */

    //buf += offset;

    memcpy(buf + offset, argv[3], len);


	/*  Clean up */

    /*  YOUR MSYNC() GOES HERE */
    if(msync(buf, len, MS_SYNC) < 0){
        perror("msync failed with error:");
        return 1;
    }
	munmap(buf, fileStat.st_size);
	close(inputFile);

	return 0;
}

