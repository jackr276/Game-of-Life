/**
 * Author: Jack Robbins
 * This is the implementation file for the header file, life.c
 */

#include "life.h"


static Grid* _initialize_grid(short rows, short cols){
	//Initialize space for the grid
	Grid* generated = (Grid*)malloc(sizeof(Grid));

	//Assign these values in here
	generated->rows = rows;
	generated->cols = cols;

	//Initialize the cell array
	generated->cells = (byte**)malloc(rows * sizeof(byte*));

	//Initialize all the columns dynamically
	for(int i = 0; i < rows; i++){
		generated->cells[i] = (byte*)calloc(cols, sizeof(byte));
	}

	//Give the pointer back. Once this pointer is passed here, it will no longer be owned by this function
	return generated;
}



static void _teardown_grid(Grid** grid){
	//First we must teardown the internal 2D array
	for(int i = 0; i < (*grid)->rows; i++){
		free((*grid)->cells[i]);
	}

	//Free the cells pointer
	free((*grid)->cells);

	//Finally free the grid pointer
	free(*grid);

	//Set to null as a warning that this is now empty
	*grid = NULL;
}


// DELETEME once done testing
void test(){
	Grid* grid;
	for(int i = 0; i < 200; i++){
		grid = _initialize_grid(500, 600);
		usleep(100);
		_teardown_grid(&grid);
	}
}


void start_game(const short rows, const short cols){
	initscr();
	test();	
}

void next_tick(){

}


void end_game(){
	endwin();
}
