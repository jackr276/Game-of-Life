/**
 * Author: Jack Robbins
 * 
 * This c file is the guts of the whole thing. From here we handle displaying and running the game of life. It is notable
 * that most functions here are static, which is C's way of making them effectively private, because no other external function
 * should be calling them
 */

#include "life.h"

/**
 * This function will initialize a grid and return a reference to a heap allocated grid structure.
 * NOTE: It is the responbility of the recipient to free this memory
 */
static Grid* _initialize_grid(const int rows, const int cols){
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


/**
 * This is a simple function that will destroy a grid for us
 * NOTE: we use a double pointer here because we set this address to NULL.
 */
static void _teardown_grid(Grid* grid){
	//First we must teardown the internal 2D array
	for(int i = 0; i < grid->rows; i++){
		free(grid->cells[i]);
	}

	//Free the cells pointer
	free(grid->cells);

	//Finally free the grid pointer
	free(grid);
}


static void _print_welcome(){
	const char title[] = "                                                                                                                                                                                            \n\
                                                                                                                                                                                                                \n\
\t\t        GGGGGGGGGGGGG                                                                        OOOOOOOOO         ffffffffffffffff       LLLLLLLLLLL               iiii      ffffffffffffffff                      \n\
\t\t     GGG::::::::::::G                                                                      OO:::::::::OO      f::::::::::::::::f      L:::::::::L              i::::i    f::::::::::::::::f                     \n\
\t\t   GG:::::::::::::::G                                                                    OO:::::::::::::OO   f::::::::::::::::::f     L:::::::::L               iiii    f::::::::::::::::::f                    \n\
\t\t  G:::::GGGGGGGG::::G                                                                   O:::::::OOO:::::::O  f::::::fffffff:::::f     LL:::::::LL                       f::::::fffffff:::::f                    \n\
\t\t G:::::G       GGGGGG  aaaaaaaaaaaaa      mmmmmmm    mmmmmmm       eeeeeeeeeeee         O::::::O   O::::::O  f:::::f       ffffff       L:::::L               iiiiiii   f:::::f       ffffff    eeeeeeeeeeee    \n\
\t\tG:::::G                a::::::::::::a   mm:::::::m  m:::::::mm   ee::::::::::::ee       O:::::O     O:::::O  f:::::f                    L:::::L               i:::::i   f:::::f               ee::::::::::::ee  \n\
\t\tG:::::G                aaaaaaaaa:::::a m::::::::::mm::::::::::m e::::::eeeee:::::ee     O:::::O     O:::::O f:::::::ffffff              L:::::L                i::::i  f:::::::ffffff        e::::::eeeee:::::ee\n\
\t\tG:::::G    GGGGGGGGGG           a::::a m::::::::::::::::::::::me::::::e     e:::::e     O:::::O     O:::::O f::::::::::::f              L:::::L                i::::i  f::::::::::::f       e::::::e     e:::::e\n\
\t\tG:::::G    G::::::::G    aaaaaaa:::::a m:::::mmm::::::mmm:::::me:::::::eeeee::::::e     O:::::O     O:::::O f::::::::::::f              L:::::L                i::::i  f::::::::::::f       e:::::::eeeee::::::e\n\
\t\tG:::::G    GGGGG::::G  aa::::::::::::a m::::m   m::::m   m::::me:::::::::::::::::e      O:::::O     O:::::O f:::::::ffffff              L:::::L                i::::i  f:::::::ffffff       e:::::::::::::::::e \n\
\t\tG:::::G        G::::G a::::aaaa::::::a m::::m   m::::m   m::::me::::::eeeeeeeeeee       O:::::O     O:::::O  f:::::f                    L:::::L                i::::i   f:::::f             e::::::eeeeeeeeeee  \n\
\t\t G:::::G       G::::Ga::::a    a:::::a m::::m   m::::m   m::::me:::::::e                O::::::O   O::::::O  f:::::f                    L:::::L         LLLLLL i::::i   f:::::f             e:::::::e           \n\
\t\t  G:::::GGGGGGGG::::Ga::::a    a:::::a m::::m   m::::m   m::::me::::::::e               O:::::::OOO:::::::O f:::::::f                 LL:::::::LLLLLLLLL:::::Li::::::i f:::::::f            e::::::::e          \n\
\t\t   GG:::::::::::::::Ga:::::aaaa::::::a m::::m   m::::m   m::::m e::::::::eeeeeeee        OO:::::::::::::OO  f:::::::f                 L::::::::::::::::::::::Li::::::i f:::::::f             e::::::::eeeeeeee  \n\
\t\t     GGG::::::GGG:::G a::::::::::aa:::am::::m   m::::m   m::::m  ee:::::::::::::e          OO:::::::::OO    f:::::::f                 L::::::::::::::::::::::Li::::::i f:::::::f              ee:::::::::::::e  \n\
\t\t        GGGGGG   GGGG  aaaaaaaaaa  aaaammmmmm   mmmmmm   mmmmmm    eeeeeeeeeeeeee            OOOOOOOOO      fffffffff                 LLLLLLLLLLLLLLLLLLLLLLLLiiiiiiii fffffffff                eeeeeeeeeeeeee  \n\
                                                                                                                                                                                                                \n\
                                                                                                                                                                                                                \n\
                                                                                                                                                                                                                \n\
                                                                                                                                                                                                                ";
 
	//Move 15 lines down or so to print our little graphic
	move(15, 0);

	//Print the title to the console
	printw(title);
	
	//Actually make it display
	refresh();

	//Print out credit
	move(36, COLS / 2 - 10);
	printw("Author: Jack Robbins\n");
	refresh();

	//Wait to let the user admire
	sleep(2);

	//Center this nicely
	move(46, COLS / 2 - 13);
	printw("<Press any key to continue>\n");
	refresh();

	getch();

}


static void _end_game(){
	//Wipe the screen clean
	clear();
	
	//Reorient to the center of the screen
	move(LINES / 2, COLS / 2 - 16);
	printw("<Program Termination Successful>");
	refresh();

	//Let the user read it
	sleep(1);


	//End ncurses mode and hard exit the program
	endwin();	
	exit(0);
}


static void _display_grid(Grid* grid){
	//Go through every cell
	for(int i = 0; i < grid->rows; i++){
		//Move the cursor down to be at the ith row
		move(i, 0);
			
		//Print a # if occupied, nothing if not
		for(int j = 0; j < grid->cols; j++){
			printw(grid->cells[i][j] ? "#" : " ");
		}
		printw("\n");
	}

	//Make this show on the screen
	refresh();
}


/**
 * Get a random starting point. In theory, this should be pretty sparse with about less than half being
 * alive. This may be changed later
 */
static Grid* _get_random_start(const int rows, const int cols){
	//Create a fresh grid
	Grid* grid = _initialize_grid(rows, cols);

	//Randomly populate this grid
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			//We want this to be kind of sparse at first, initial idea is we only populate with a 1 if we can divide by 3
			grid->cells[i][j] = (rand() % 3 != 0) ? 0 : 1; 
		}
	}

	//And that's all, our grid should be randomly populated now
	return grid;
}


/**
 * Everything in the game of life revolves around how many neighbors a cell has. Because of this, the number of neighbors
 * is the most critical part of our game
 */
static int _num_living_neighbors(byte** grid, const int rows, const int cols, const int cell_row, const int cell_col){
	int num_neighbors = 0;
	int neighbor_row;
	int neighbor_col;

	/**
	* We need to check all of the 8 neighboring cells to this cell, just to give a visual:
	*                         1 2 3
	*                         4 * 5
	*                         6 7 8
	* In order to effectively count how many neighbors there are
	*
	* NOTE: If we go out of bounds of the grid, we will simply wrap around in whatever direction is appropriate
	*/

	//TOP LEFT
	//Decide which row coordinates to use
	//If we underflow, we'll rap around
	if(cell_row - 1 >= 0){
		neighbor_row = cell_row - 1;
	} else {
		neighbor_row = rows - 1;
	}

	//Decide which col coordinates to use
	if(cell_col - 1 >= 0){
		neighbor_col = cell_col - 1;
	} else {
		neighbor_col = cols - 1;
	}

	//We'll just add what we have here -- remember 1 = alive, 0 = dead
	num_neighbors += grid[neighbor_row][neighbor_col];

	//ABOVE
	//Check directly above, column is the same here
	neighbor_col = cell_col;

	//Again if we underflow the rows just wrap around
	if(cell_row - 1 >= 0){
		neighbor_row = cell_row - 1;
	} else {
		neighbor_row = rows - 1;	
	}

	//Again add what we have	
	num_neighbors += grid[neighbor_row][neighbor_col];

	//TOP RIGHT
	//Check to the top right, if it is valid. If not treat it as dead	
	//If we underflow, we'll rap around
	if(cell_row - 1 >= 0){
		neighbor_row = cell_row - 1;
	} else {
		neighbor_row = rows - 1;
	}

	//If we overflow columns, we'll also wrap around
	if(cell_col + 1 < cols){
		neighbor_col = cell_col + 1;
	} else {
		neighbor_col = 0;
	}

	//Again add what we have	
	num_neighbors += grid[neighbor_row][neighbor_col];

	//LEFT
	//Check directly to the left, row is the same
	neighbor_row = cell_row;
	
	//If we underflow wrap around
	if(cell_col - 1 >= 0){
		neighbor_col = cell_col - 1;
	} else {
		neighbor_col = cols - 1;
	}

	//Again add what we have	
	num_neighbors += grid[neighbor_row][neighbor_col];

	//RIGHT
	//Check directly to the right, row is the same
	neighbor_row = cell_row;

	//If we overflow the columns
	if(cell_col + 1 < cols){
		neighbor_col = cell_col + 1;
	} else {
		neighbor_col = 0;
	}

	//Again add what we have	
	num_neighbors += grid[neighbor_row][neighbor_col];

	//BOTTOM LEFT
	//Check to the bottom left
	//Wrap around if we overflow rows
	if(cell_row + 1 < rows){
		neighbor_row = cell_row + 1;
	} else {
		neighbor_row = 0;
	}

	//If we underflow cols, wrap around 
	if(cell_col - 1 >= 0){
		neighbor_col = cell_col - 1;
	} else {
		neighbor_col = cols - 1;
	}

	//Again add what we have	
	num_neighbors += grid[neighbor_row][neighbor_col];

	//BELOW
	//Check directly below, column the same
	neighbor_col = cell_col;

	//If we overflow rows
	if(cell_row + 1 < rows){
		neighbor_row = cell_row + 1;
	} else {
		neighbor_row = 0;
	}

	//Again add what we have	
	num_neighbors += grid[neighbor_row][neighbor_col];

	//BOTTOM RIGHT 
	//Check to the bottom right
	//If we overflow rows we'll rap around
	if(cell_row + 1 < rows){
		neighbor_row = cell_row + 1;
	} else {
		neighbor_row = 0;
	}

	//Same for columns
	if(cell_col + 1 < cols){
		neighbor_col = cell_col + 1;
	} else {
		neighbor_col = 0;
	}

	//Again add what we have	
	num_neighbors += grid[neighbor_row][neighbor_col];

	return num_neighbors;
}


static Grid* _next_tick(Grid* previous){
	//Make a new grid
	Grid* next_gen = _initialize_grid(previous->rows, previous->cols);
	int num_living_neighbors;

	//Cycle through all of the cells
	for(int i = 0; i < previous->rows; i++)	{
		for(int j = 0; j < previous->cols; j++){
			//Count how many neighbors this cell has -- this drives everything in the game
			num_living_neighbors = _num_living_neighbors(previous->cells, previous->rows, previous->cols, i, j);	
	
			/* Birth/dying logic based on number of neighbors */

			//Any living cell with fewer than 2 live neighbors dies
			if(previous->cells[i][j] == 1 && num_living_neighbors < 2){
				next_gen->cells[i][j] = 0;

			//Any living cell with 2 or 3 neighbors lives to the next generation
			} else if(previous->cells[i][j] == 1 && (num_living_neighbors == 2 || num_living_neighbors == 3)){
				next_gen->cells[i][j] = 1;

			//Any living cell with more than 3 neighbors dies
			} else if(previous->cells[i][j] == 1 && num_living_neighbors > 3){
				next_gen->cells[i][j] = 0;

			//Any dead cell with exactly 3 live neighbors comes to life
			} else if(previous->cells[i][j] == 0 && num_living_neighbors == 3){
				next_gen->cells[i][j] = 1;

			} else {
				//By default, all cells are dead
				next_gen->cells[i][j] = 0;
			}
		}
	}

	//Free up all the memory of the previous grid
	_teardown_grid(previous);

	//Return a reference to the next grid
	return next_gen;
}



void run_game(){	
	//Initialize the screen into ncurses mode
	initscr();

	//If the terminal is the wrong size, we'll just quit and tell the user to retry
	if(LINES < 52 || COLS < 224){
		//Print a nice error
		move(LINES / 2 - 3, 0);
		printw("==============================================================================================================================\n");
		printw("Display Error: Terminal Window must be at least 52 lines tall by 224 columns wide for proper display. Please resize and retry.\n");
		printw("==============================================================================================================================\n\n");

		//Flush the buffer so it displays
		refresh();
		
		//Let the user read the error
		sleep(5);

		//End the ncurses session and exit with an error code
		endwin();
		exit(1);
	}

	//We will now save the rows and columns as constants
	const int rows = LINES;
	const int cols = COLS;

	//Raw mode, <CTRL-C> won't quit
	raw();

	//Don't show keys on the screen
	noecho();

	//Put the cursor in invisible mode
	curs_set(0);

	//We just initialize this as null for right now
	char user_input = '\0';

	//Game startup mode, we only move forward once some key is pressed
	_print_welcome();

	//Wipe the screen
	clear();

	//We don't want to wait for user input, so set up this no delay
	nodelay(stdscr, 1);

	printw("Press <q> to quit at any time\n");
	refresh();

	//Refresh user input in the rare event they entered 'q' first
	user_input = '\0';	

	//We will keep track of the "generations of the game"
	int generation = 1;
	
	//Initially the first grid is a random one
	Grid* current = _get_random_start(rows, cols);
	
	//Main game loop, while the user lets it go, we will run forever
	//Idea of the main loop: Display -> wait -> get next & repeat
	while(user_input != 'q'){
		//Display the grid
		_display_grid(current);

		//Wait 1 second
		usleep(230000);
		
		//Get the next grid
		current = _next_tick(current);

		//Grab the user input
		user_input = getch();
		generation++;
	}
	
	//If we get here, we know that it is time to terminate our game method
	_end_game();
}
