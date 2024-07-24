# Author: Jack Robbins
# Simple C runner script

#!/bin/bash

if [[ ! -d ./out ]]; then
	mkdir out
fi

# Clean out whatever already exists in here
rm -r out/*

gcc -Wall -Wextra ./src/main.c -o ./out/main

./out/main
