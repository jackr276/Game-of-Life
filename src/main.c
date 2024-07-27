/**
 * Author: Jack Robbins
 * This is the entry point for the game of life terminal display
 */

#include <unistd.h>
#include "life/life.h"


int main(void){
	start_game(40, 60);
	end_game();
	

	return 0;
}
