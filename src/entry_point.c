/**
 * Author: Jack Robbins
 * This is the entry point for Conway's game of life, in C
 */

#include <stdio.h>
#include <unistd.h>

int main(void){
	printf("\n");
	//Flush buffer immediately
	for(int i = 0; i < 35; i++){
		printf("=");
		fflush(stdout);
		usleep(1000000);
	}
	printf("\n");
}


