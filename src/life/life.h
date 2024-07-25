/**
 * Author: Jack Robbins
 * This file contains all the needed methods for the life game to run
 */

#ifndef LIFE_H
#define LIFE_H

/**
 * The cell is the building block for the entire GoL
 */
typedef struct {
	short is_alive;
} Cell;


/**
 * The grid for all of the cells. This must be dynamically allocated,
 * due to the rules of C static array declarations
 */
typedef struct{
	const short rows;
	const short cols;
	Cell** cells;
} Grid;


void start_game(const short rows, const short cols);
Grid* initialize_grid(short N);
void next_tick();
void draw_grid(Grid* grid);
void end_game();

#endif
