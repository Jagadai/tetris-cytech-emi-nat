CC = gcc
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: tetris

%.o: %.c functions.h
	$(CC) -c $< -o $@

tetris: $(OBJ)
	$(CC) $^ -o $@
