# Makefile for game of life project
CC = gcc
CFLAGS = -Wall -Wextra -c
PROGS = life
OUT = ./out

all: $(PROGS)

main.o: ./src/main.c
	$(CC) $(CFLAGS) ./src/main.c -o $(OUT)/main.o -lncurses

life.o: ./src/life/life.c
	$(CC) $(CFLAGS) ./src/life/life.c -o $(OUT)/life.o -lncurses

life: life.o main.o
	$(CC) $(OUT)/life.o $(OUT)/main.o -o $(OUT)/life -lncurses

run: life
	$(OUT)/life

clean:
	rm -f $(OUT)/*

