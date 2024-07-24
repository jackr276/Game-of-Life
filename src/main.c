/**
 * Author: Jack Robbins
 * This is the entry point for the game of life terminal display
 */


#include <stdio.h>
#include <ncurses.h>
int main(void){
	//Initialize ncurses
	initscr();
	printf("I work\n");
	refresh();

	//End the Ncursers mode
	endwin();
	return 0;
}
