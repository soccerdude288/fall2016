/*
* Taylor Earl
* CS3210
* 10/1/2016
* password.c
*/


#include <termios.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <term.h>
#include <curses.h>
#include <string.h>

#define PASSWORD_LEN 50
#define USERNAME_LEN 50

int main() {
	struct termios initialrsettings, newrsettings; 
	char password[PASSWORD_LEN + 1]; 
	char username[USERNAME_LEN+1];
	tcgetattr(fileno(stdin), &initialrsettings); 


	//GET ROWS AND COLUMN NUMBERS
	int nrows, ncolumns;
	setupterm(NULL, fileno(stdout),0); 
	nrows = tigetnum("lines"); 
	ncolumns = tigetnum("cols"); 



	//MOVE INPUT TO MIDDLE OF SCREEN AND CLEAR
	char *cursor, *clear; 
	char *esc_sequence; 
	cursor = tigetstr("cup"); 
	clear = tigetstr("clear");

	tputs(clear, 1, putchar);
	esc_sequence = tparm(cursor,nrows/2, (ncolumns/2) - 10); 
	putp(esc_sequence);

	//TAKE USERNAME INPUT
	printf("username: ");
	fgets(username, USERNAME_LEN, stdin);
 
 	//MOVE INPUT BACK TO MIDDLE
	cursor = tigetstr("cup"); 
	esc_sequence = tparm(cursor,(nrows/2) + 1, (ncolumns/2) - 10); 
	putp(esc_sequence);

	//TURN OFF ECHO
	newrsettings = initialrsettings; 
	newrsettings.c_lflag &= ~ECHO;
	printf("password: "); 

	if(tcsetattr(fileno(stdin), TCSAFLUSH, &newrsettings) != 0){ 
		fprintf(stderr,"Could not set attributes\n"); 
	}else { 
		//TAKE PASSWORD INPUT
		fgets(password, PASSWORD_LEN, stdin); 

		//STRIP RETURN CHARACTER
		password[strcspn(password, "\n")] = 0;
		
		//MOVE INPUT TO BOTTOM CORNER OF PAGE
		cursor = tigetstr("cup"); 
		esc_sequence = tparm(cursor, ((nrows-2) - 1), 1); 
		putp(esc_sequence);

		//REVERT BACK TO INITIAL SETTINGS
		tcsetattr(fileno(stdin), TCSANOW, &initialrsettings); 
		fprintf(stdout, "\nYou entered %s", password); 
	}
	//AGAIN REVERT OUT PUT FOR EXIT OF PROGRAM 
	cursor = tigetstr("cup"); 
	esc_sequence = tparm(cursor, (nrows-1), 0); 
	putp(esc_sequence);

	exit(0);
}