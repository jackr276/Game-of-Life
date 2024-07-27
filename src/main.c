/**
 * Author: Jack Robbins
 * This is the entry point for the game of life terminal display
 */

#include <unistd.h>
#include "life/life.h"


int main(void){
	run_game(LINES, COLS);	
	return 0;
}
