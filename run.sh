# Author: Jack Robbins
# Simple C runner script

#!/bin/bash

if [[ ! -d ./out ]]; then
	mkdir out
fi

# Clean out whatever already exists in here
rm -r out/*

# IMPORTANT -- never experienced this with gcc, but the link for ncurses must come at the end
gcc -o ./out/main -Wall -Wextra ./src/main.c ./src/life/life.c -lncurses  

./out/main
