# Game of Life
Author: [Jack Robbins](https://www.github.com/jackr276)

![Screenshot from 2024-08-03 13-35-52](https://github.com/user-attachments/assets/00b15dc1-298b-40ee-844d-9367070d4b91)

## Conway's Game of Life
John Conway's Game of Life is perhaps the most famous "0 Player Game" ever made. Conway's Game of Life's evolution is entirely determined by its initial state, and it is impossible to predict what a certain pattern will do without running the actual pattern. Each "generation" of the game is a grid of cells, often called Cellular Automata, that interact with eachother via a determined set of rules that will dictate if a given cell lives or dies.

The rules of the game are very simple, and are as follows:
 1. Any living cell with less than 2 live neighbors dies
 2. Any living cell with 2 or 3 live neighbors survives to the next generation
 3. Any living cell with more than 3 neighbors dies
 4. Any dead cell with exactly 3 live neighbors comes to life

With these simple rules, a game board can come to life with as long as there is a given seed. The board will continue to evolve forever, or die out completely. Whatever the outcome is, it is impossible to tell without letting the game run out to infinity. The Game of Life is truly fascinating to me and I intend to do more with it in the future. This program is just a fun proof of concept to get the basics working using ncurses in the terminal.

## Running this Program
To run this program, first clone the repository and navigate to the directory that it downloaded under. For your convenience, a [runner script](https://github.com/jackr276/Game-of-Life/blob/main/run.sh) has been provided for compiling/running the program. All you must do is run the following commands:
```console
example@bash: ~/Arithmetic-Expression-Evaluator $ chmod +x run.sh
example@bash: ~/Arithmetic-Expression-Evaluator $ ./run.sh
```
It is important to note that upon running the final command, your screen will enter '`ncurses`' mode, meaning that there is no typing or <CTRL-C> exit ability. The program will first display the welcome screen shown above, or this welcome screen if your terminal window is too small:   

![Screenshot from 2024-08-03 13-47-46](https://github.com/user-attachments/assets/6cd53813-7b45-4412-a3c1-58467127b067)

After the welcome screen shows the `<Press any key to begin>` command, hitting any key will immediately launch the game, at which point you'll immediately begin seeing the Game of Life play out in front of you like this:   

![Screenshot from 2024-08-03 13-48-50](https://github.com/user-attachments/assets/fc90c50e-6d15-48db-a09a-11c88c80b043)

In order to quit the game, you must press '`q`', which will immediately kill the program and take you to an exit screen.

## Conclusion & Future Ideas
If this is something that you are interested in, I would greatly encourage you to download the program and take it for a spin. It is very simple in its current iteration, but this also has the benefit of making it extremely lightweight, being written in pure C, and easy to understand. My future ideas for this program include adding the ability for the user to create their own random seed for the board, as well as integrating patterns like Gliders and Gosper Guns. Hopefully, I'll have some free time to get around to it. Enjoy the Game of Life!

