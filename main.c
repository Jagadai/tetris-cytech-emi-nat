#include "functions.h"

int main(){
	srand(time(NULL));
	int* score;
	int** grid;
	int loser = 0;
	int actualpieceid;
	int orientation;
	char column;
	piece actualpiece;
	score = malloc(sizeof(int));
	*score = 0;
	grid = malloc((SIDE+1)*sizeof(int*));	//Allocation des lignes du tableau
	if (grid == NULL){
		printf("Allocaion failure");
		exit(1);
	}
	for(int i=0;i<(SIDE+1);i++){		//Allocation colonnes pour chaque ligne
		grid[i]=malloc(SIDE*sizeof(int));
		if (grid[i]==NULL){
			printf("Allocation failure");
			exit(2);
		}
	}
	initGrid(grid);
	do{	//On joue tant qu'on a pas perdu
		display(grid);
		actualpieceid = block();
		if (actualpieceid !=1){
			printf("Choisir l'orientation de la pièce puis la colonne avec la lettre\n");
		}
		displayPieceChoice(actualpieceid);
		if (actualpieceid !=1){
			scanf("%d", &orientation);
		}
		printf("\n");
		do{	//On scan la colomne jusqu'à ce qu'elle soit valide
			scanf("%c", &column);
		}while(letterConversion(column)<65 | letterConversion(column)>74);
		column = column - 65;
		actualpiece.location = column;
		if (lost(grid, actualpiece) == 0){
			//printf("L'id de la pièce est %d\n", actualpieceid);
			actualpiece = finalshape(orientation, actualpieceid);
			placePiece(grid, actualpiece);
			cleaning(grid, score);
		}
		else loser = 1;
		//loser = 1; //Juste pour test
	}while(loser == 0);
	scoreSave(score);
	free(score);
	free(grid);
	return 0;
}
