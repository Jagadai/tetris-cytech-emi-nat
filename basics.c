#include "functions.h"

unsigned long getTimeMicroSec(){
	/*
	Role: Give the actual time in microseconds
	Output: int:actual time in microseconds
	*/
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (1000000 * tv.tv_sec) + tv.tv_usec;
}

char box(int p){
	/*
	Role: Displays a box with the correct character
	Inputs: 
		int p: The number of the character in the box (0 or 1)
	Output: 
		int displaybox: The ASCII code of the character associated (@ or ' ')
	*/
	if (p != 0 & p !=1){
		printf("The box contains incorrect data");
		exit(20);
	}
	int displayBox;
	switch(p){
		case 0:
			displayBox = 32;
			break;
		case 1:
			displayBox = 64;
			break;
		default:
			displayBox = 69;
			break;
	}
	return displayBox;
}

void display(int** grid){
	/*
	Role: Displays the game grid
	Inputs: 
		int** grid: the game grid
	*/
	if (grid == NULL){
		printf("The game grid is empty");
		exit(21);
	}
	printf("Voici votre grille: \n ");
	for (int i=65; i<(SIDE+65); i++){
		printf("%c ", i);
	}
	printf("\n");
	for (int i=0; i<SIDE; i++){
		printf("|", i+1);
		for (int j=0; j<SIDE; j++){
			printf("%c|", box(grid[i][j]));
		}
		printf("\n");
	}

}

void initGrid(int** grid){
	/*
	Role: Initialize the game grid with only 0 and only 1 for the "floor"
	Inputs: 
		int** grid: the game grid
	*/
	if (grid == NULL){
		printf("The game grid is empty");
		exit(22);
	}
	for(int i=0;i<SIDE;i++){	//initialisation of all the game grid
		for(int j=0;j<SIDE;j++){
			grid[i][j]=0;
		}
	}
	for(int j=0;j<SIDE;j++){	//Initialisation of the 'floor'
		grid[SIDE][j]=1;
	}
}

int possiblePlacement(int** grid, piece npiece, int depth){
	/*
	Role: Check if the piece can be placed at this place
	Inputs: 
		int** grid: the game grid
		piece npiece: the piece we want to place
		int depth: the depth the piece must be placed
	Output: 
		int: 0 if the piece can't be placed and 1 else
	*/
	if (grid == NULL){
		printf("The game grid is empty");
		exit(23);
	}
	if (depth > SIDE){
		printf("Impossible piece depth");
		exit(24);
	}
	for(int i=0; i<npiece.lenght; i++){	//Vérify if we can put the piece here
		for(int j=0; j<npiece.width; j++){
			if (npiece.form[i][j] == grid[depth+i][npiece.location + j] & npiece.form[i][j] == 1){
				return 0;
			}
		}
	}
	return 1;
}
int lost(int** grid, piece npiece){
	/*
	Role: Check if the player lost the game
	Inputs: 
		int** grid: the game grid
		piece npiece: the piece we want to place
	Output: 
		int: 1 if the player lost and 0 else
	*/
	if (grid == NULL){
		printf("The game grid is empty");
		exit(25);
	}
	if (possiblePlacement(grid, npiece, 0) == 0) return 1;
	return 0;
}

void placePiece(int** grid, piece npiece){
	/*
	Role: Place the new piece in the game
	Inputs: 
		int** grid: the game grid
		piece npiece: the piece we want to place
	*/
	if (grid == NULL){
		printf("The game grid is empty");
		exit(26);
	}
	int depth = 1;	//The first piece has been verified by lost
	while (possiblePlacement(grid, npiece, depth)){	//While no collision or floor not touched the piece comes down
		depth++;
	}
	depth--; //We go up a notch for placement
	for(int i=0; i<npiece.lenght; i++){	//Place the piece in the grid
		for(int j=0; j<npiece.width; j++){
			if (npiece.form[i][j] == 1){ //We copy the box only if it's full
				grid[depth+i][npiece.location+j] = npiece.form[i][j];
			}
		}
	}
}

int letterConversion(char letter){	//convertie la lettre de la colonne si passée en minuscule
	/*
	Role: Convert the letter if it's lowercase letter
	Inputs: 
		char letter: the letter we must convert
	Output: 
		char letter: the letter converted
	*/
	if (letter<107 & letter>96){
		letter-= 32;
	}
	return letter;
}
