/**
 * Author: Jack Robbins
 * This is the implementation file for the header file, life.c
 */

#include "life.h"

void start_game(const short rows, const short cols){
	initscr();
	
}

Grid* initialize_grid(short rows, short cols){
	Grid generated;
	generated.rows = rows;
	generated.cols = cols;

}

void next_tick(){

}


void end_game(){
	endwin();
}
