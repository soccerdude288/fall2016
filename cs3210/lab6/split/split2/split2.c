//http://icoder.vishalmishra.in/2015/02/split-windows-in-ncurses-in-c.html

#include <curses.h>
#include <stdlib.h>
#include <unistd.h> 

int main(int argc, char *argv[])
{
WINDOW *a, *b, *c;
char command[100];
//int maxx, maxy, halfx, halfy;
int maxx, maxy, halfx, halfy;


initscr();
refresh();
start_color();

init_pair(1, COLOR_GREEN, COLOR_BLACK);
init_pair(2, COLOR_RED, COLOR_BLACK);
init_pair(3, COLOR_BLUE, COLOR_BLACK);

/* calculate window sizes and locations */
getmaxyx(stdscr, maxy, maxx);
//halfx = maxx >> 1;
//halfy = maxy >> 1;

halfx = maxx/2;
halfy = maxy/2;



/* create four windows to fill the screen */
a = newwin(halfy, 0, 0, 0);
c = newwin(halfy, 0, halfy, 0);
b = newwin(halfy - 1, 0, halfy + 1, 0);


scrollok(a, TRUE);
scrollok(b, TRUE);

//mvwaddstr(a, 0, 0, "This is window A\n");
wbkgd(a, COLOR_PAIR(1));
wrefresh(a);

wbkgd(c, COLOR_PAIR(3));
wrefresh(c);
whline(c, ACS_HLINE, maxx);

//mvwaddstr(b, 0, 0, "This is window B\n");
wbkgd(b, COLOR_PAIR(2));
wrefresh(b);

wbkgd(c, COLOR_PAIR(3));
wrefresh(c);
whline(c, ACS_HLINE, maxx);

int i= 1;

noecho();

int ch;
nodelay(stdscr, TRUE);
while((ch = getch()) == ERR){
	wprintw(a, "Count up: %d\n", i);
	wprintw(b, "Count down: -%d\n", i);
	i++;
	wrefresh(a);
	wrefresh(b);
	usleep(250000);
}


//wscanw(a,"%s",command);

/* Print command string in window4*/
//wprintw(b,"%s",command);
//wrefresh(b);
//getch();
echo();
sleep(3);
endwin();
return 0;
}