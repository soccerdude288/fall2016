#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

int
main(int argc, char *argv[]){

    printf(1, "Taylor Earl\n");

    //char buf[8192];
    int fd;

    fd = open("tom.txt", O_CREATE|O_RDWR);
    if(fd < 0){
	    printf(1, "error creating file.\n");
    };
    char buf1[11] = {"1 2 3 4 \n"};
    //write(fd, buf1, 512);
   
/* 
    for(int i = 0; i < 1; i++){
	//((int*)buf1)[0] = i;
        if(write(fd, buf1, 8) != 8){
            printf(1, "error: write big file failed\n", i);
            exit();
        };
    };
*/
    if(write(fd, buf1, 9) != 9){
    printf(1, "error: write big file failed\n");
    exit();
    }

	
  
    close(fd);
    exit();
}

