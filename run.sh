# Author: Jack Robbins
# Simple C runner script

#!/bin/bash

if [[ ! -d ./out ]]; then
	mkdir out
fi

gcc -Wall -Wextra ./src/entry_point.c -o ./out/entry_point

./out/entry_point
