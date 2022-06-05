#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#define SIDE 10	//Taille de la grille en largeur et longueur

typedef struct{
	int** form;
	int location;
	int lenght;
	int width;
} piece;

//scores
int fullLine(int* line);
void clearLine(int* line);
void cleaning(int** grid, int* score);
void actualscore(int* score, int combo);
void scoreSave(int* score);

//basics
char box(int p);
void display(int** grid);
void randomGrid(int** grid);
void initGrid(int** grid);
int possiblePlacement(int** grid, piece npiece, int depth);
int lost(int** grid, piece npiece);
piece adjustment(piece npiece);
void placePiece(int** grid, piece npiece);
int letterConversion(int letter);

//piece
int block();
piece finalshape(int orientation, int shapes);
void diplayPieceChoice(int pieceid);
void pieceCopy(int** piece1, int piece2[4][4], int lenght, int width);