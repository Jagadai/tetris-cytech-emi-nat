#include "functions.h"

int main(){
	srand(time(NULL));
	int c;
	int* score;
	int** grid;
	int loser = 0;
	int actualpieceid;
	int orientation;
	int* nborientation;
	char column;
	int time1;
	int time2;
	int intverifier = 0;	//To verify if the scan took an int
	int buganticip=0;	//Creation of a variable to detect if the user doesn't enter an int 
	piece actualpiece;
	score = malloc(sizeof(int));
	nborientation = malloc(sizeof(int));
	grid = malloc((SIDE+1)*sizeof(int*));	//Allocation of the array lines
	if (score == NULL){
		printf("Allocaion failure");
		exit(10);
	}
	if (grid == NULL){
		printf("Allocaion failure");
		exit(11);
	}
	for(int i=0;i<(SIDE+1);i++){		//Allocation of the array columns
		grid[i]=malloc(SIDE*sizeof(int));
		if (grid[i]==NULL){
			printf("Allocation failure");
			exit(12);
		}
	}
	*score = 0;
	initGrid(grid);
	do{	//We play while we don't lose
		display(grid);
		actualpieceid = block(nborientation);
		displayPieceChoice(actualpieceid);
		printf("Vous avez 10 secondes pour placer votre pièce\n");
		time1 = getTimeMicroSec();
		if (actualpieceid !=1){
			buganticip = 0;
			do{
				if (buganticip<10){
					if(buganticip <1){
						printf("Entrez le chiffre de l'orientation: \n");
					}
					intverifier = scanf("%d", &orientation);
					buganticip++;
				}
				else{
					printf("On a dit d'entrer un chiffre, puisque c'est comme ça on vous laisse pas le choix puis on joue un peu à votre place\n");
					orientation = 1;
				}
			}while(orientation<=0 | orientation>*nborientation | intverifier != 1 & buganticip < 10);
		}
		printf("\n");
		printf("Entrez la lettre de la colonne: ");
		do{	//We scan the column until it's valid
			column = getchar();
			//scanf("%c", &column);
		}while(letterConversion(column)<65 | letterConversion(column)>74-actualpiece.width+1); 	//We verify if the piece enter well in the game grid
		column = letterConversion(column) - 65;
		time2 = getTimeMicroSec();
		if (time2 - time1 >= 10000000){
			printf("Vous avez mis trop de temps pour répondre, la pièce est placée au hasard\n");
			actualpiece = finalshape(1+rand()%*nborientation, actualpieceid);
			actualpiece.location = rand()%(10-actualpiece.width);
		}
		else{
			actualpiece = finalshape(orientation, actualpieceid);
			actualpiece.location = column;
		}
		if (lost(grid, actualpiece) == 0){	//We put the piece only if we don't lose by placing it
			placePiece(grid, actualpiece);
			cleaning(grid, score);
		}
		else loser = 1;
	}while(loser == 0);
	scoreSave(score);
	free(nborientation);
	free(score);
	free(grid);
	return 0;
}
