/**
 * Author: Jack Robbins
 * This file contains all the needed methods for the life game to run
 */

#ifndef LIFE_H
#define LIFE_H

#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

typedef unsigned char byte;

/**
 * The grid for all of the cells. This must be dynamically allocated,
 * due to the rules of C static array declarations
 */
typedef struct{
	short rows;
	short cols;
	byte** cells;
} Grid;


void start_game(short rows, short cols);
void next_tick();
void draw_grid(Grid* grid);
void end_game();

#endif
