/**
 * Author: Jack Robbins
 * This is the entry point for the game of life terminal display
 */

#include <stdio.h>
#include <unistd.h>
//Ncurses library for our terminal display
#include <ncurses.h>
#include "life/life.h"

int main(void){
	//Initialize ncurses
	initscr();

	printf("I work\n");
	sleep(2);
	refresh();

	//End the Ncursers mode
	endwin();
	return 0;
}
