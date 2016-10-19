/*  Ted Cowan, CS3210 Lab 4 Skeleton File */

/*Taylor Earl
 * CS3210
 * 9/22/2016
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>




void usage(){
	printf("Usage: userinfo -? -h -t -u username\n -h show hostname\n -t show time and date\n -u show username, uid, gid, home dir, shell and GECOS\n -? show usage\n");

};

int main (int argc, char *argv[]) {
	int c;
	//int digit_optind = 0;
	//int aopt = 0, bopt =0;
	//char *copt = 0, *dopt =0;


	char host[128];
	time_t current_time;
	char* c_time_string;
	struct passwd *pwd;
	while ( (c = getopt(argc, argv, "htu?")) != -1){

		switch(c) {
			case 'h':

				gethostname(host, 128);
				printf("hostname:%s\n", host);
				return 0;
			case 't':
				current_time = time(NULL);
				c_time_string = ctime(&current_time);
				printf("Current time is %s", c_time_string);
				return 0;
			case 'u':

	           pwd = getpwnam(argv[2]);

	            printf("username: %s\n", pwd -> pw_gecos);
				printf("user ID: %ld\n",(long) pwd -> pw_uid);
				printf("group ID: %ld\n",(long) pwd -> pw_gid);
				printf("home directory: %s\n", pwd -> pw_dir);
	            printf("shell: %s\n", pwd -> pw_shell);
	           	printf("gecos information: %s\n", pwd -> pw_gecos);				
	           	return 0;
			case '?':
				usage();
				return 1;
		}
	}
	return 0;
}

