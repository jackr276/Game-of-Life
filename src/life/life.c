/**
 * Author: Jack Robbins
 * 
 * This header file contains all of the method needed to maintain the game state
 * for the Game of Life
 */

#include "life.h"
#include <ncurses.h>
#include <string.h>
#include <unistd.h>


/**
 * This function will initialize a grid and return a reference to a heap allocated grid structure.
 * NOTE: It is the responbility of the recipient to free this memory
 */
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


/**
 * This is a simple function that will destroy a grid for us
 * NOTE: we use a double pointer here because we set this address to NULL.
 */
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


void _print_welcome(){
	const char title[] = "                                                                                                                                                                                            \n\
                                                                                                                                                                                                                \n\
\t        GGGGGGGGGGGGG                                                                        OOOOOOOOO         ffffffffffffffff       LLLLLLLLLLL               iiii      ffffffffffffffff                      \n\
\t     GGG::::::::::::G                                                                      OO:::::::::OO      f::::::::::::::::f      L:::::::::L              i::::i    f::::::::::::::::f                     \n\
\t   GG:::::::::::::::G                                                                    OO:::::::::::::OO   f::::::::::::::::::f     L:::::::::L               iiii    f::::::::::::::::::f                    \n\
\t  G:::::GGGGGGGG::::G                                                                   O:::::::OOO:::::::O  f::::::fffffff:::::f     LL:::::::LL                       f::::::fffffff:::::f                    \n\
\t G:::::G       GGGGGG  aaaaaaaaaaaaa      mmmmmmm    mmmmmmm       eeeeeeeeeeee         O::::::O   O::::::O  f:::::f       ffffff       L:::::L               iiiiiii   f:::::f       ffffff    eeeeeeeeeeee    \n\
\tG:::::G                a::::::::::::a   mm:::::::m  m:::::::mm   ee::::::::::::ee       O:::::O     O:::::O  f:::::f                    L:::::L               i:::::i   f:::::f               ee::::::::::::ee  \n\
\tG:::::G                aaaaaaaaa:::::a m::::::::::mm::::::::::m e::::::eeeee:::::ee     O:::::O     O:::::O f:::::::ffffff              L:::::L                i::::i  f:::::::ffffff        e::::::eeeee:::::ee\n\
\tG:::::G    GGGGGGGGGG           a::::a m::::::::::::::::::::::me::::::e     e:::::e     O:::::O     O:::::O f::::::::::::f              L:::::L                i::::i  f::::::::::::f       e::::::e     e:::::e\n\
\tG:::::G    G::::::::G    aaaaaaa:::::a m:::::mmm::::::mmm:::::me:::::::eeeee::::::e     O:::::O     O:::::O f::::::::::::f              L:::::L                i::::i  f::::::::::::f       e:::::::eeeee::::::e\n\
\tG:::::G    GGGGG::::G  aa::::::::::::a m::::m   m::::m   m::::me:::::::::::::::::e      O:::::O     O:::::O f:::::::ffffff              L:::::L                i::::i  f:::::::ffffff       e:::::::::::::::::e \n\
\tG:::::G        G::::G a::::aaaa::::::a m::::m   m::::m   m::::me::::::eeeeeeeeeee       O:::::O     O:::::O  f:::::f                    L:::::L                i::::i   f:::::f             e::::::eeeeeeeeeee  \n\
\t G:::::G       G::::Ga::::a    a:::::a m::::m   m::::m   m::::me:::::::e                O::::::O   O::::::O  f:::::f                    L:::::L         LLLLLL i::::i   f:::::f             e:::::::e           \n\
\t  G:::::GGGGGGGG::::Ga::::a    a:::::a m::::m   m::::m   m::::me::::::::e               O:::::::OOO:::::::O f:::::::f                 LL:::::::LLLLLLLLL:::::Li::::::i f:::::::f            e::::::::e          \n\
\t   GG:::::::::::::::Ga:::::aaaa::::::a m::::m   m::::m   m::::m e::::::::eeeeeeee        OO:::::::::::::OO  f:::::::f                 L::::::::::::::::::::::Li::::::i f:::::::f             e::::::::eeeeeeee  \n\
\t     GGG::::::GGG:::G a::::::::::aa:::am::::m   m::::m   m::::m  ee:::::::::::::e          OO:::::::::OO    f:::::::f                 L::::::::::::::::::::::Li::::::i f:::::::f              ee:::::::::::::e  \n\
\t        GGGGGG   GGGG  aaaaaaaaaa  aaaammmmmm   mmmmmm   mmmmmm    eeeeeeeeeeeeee            OOOOOOOOO      fffffffff                 LLLLLLLLLLLLLLLLLLLLLLLLiiiiiiii fffffffff                eeeeeeeeeeeeee  \n\
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

void _end_game(){
	endwin();
}

void run_game(const short rows, const short cols){
	//Initialize the screen into ncurses mode
	initscr();

	//Raw mode, <CTRL-C> won't quit
	raw();

	//Don't show keys on the screen
	noecho();

	curs_set(0);

	//We just initialize this as null for right now
	char user_input = '\0';

	//Game startup mode, we only move forward once some key is pressed
	_print_welcome();

	clear();

	//We don't want to wait for user input, so set up this no delay
	nodelay(stdscr, 1);

	printw("Press <q> to quit at any time");

	//Refresh user input in the rare event they enterred 'q' first
	user_input = '\0';	

	int i = 1;
	//Here is the main game loop that we have here
	while(user_input != 'q'){
		test();
		printw("Iter %d\n", i);
		i++;
		refresh();
		user_input = getch();
	}
	
	//If we get here, we know that it is time to terminate our game method
	_end_game();
}


/**
 * The next tick function will 
 */
Grid* next_tick(Grid* current){
	//Initialize the next grid
	Grid* next_grid = _initialize_grid(current->rows, current->cols);

	return next_grid;
}
