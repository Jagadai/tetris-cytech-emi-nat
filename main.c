#include "functions.h"

int main(){
	srand(time(NULL));
	int* score;
	int** grid;
	int loser = 0;
	int actualpieceid;
	int orientation;
	int* nborientation;
	char column;
	piece actualpiece;
	score = malloc(sizeof(int));
	nborientation = malloc(sizeof(int));
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
		actualpieceid = block(nborientation);
		displayPieceChoice(actualpieceid);
		if (actualpieceid !=1){
			do{
				printf("Entrez l'orientation: ");
				scanf("%d", &orientation);
			}while(orientation<=0 | orientation>*nborientation);
		}
		printf("\n");
		actualpiece = finalshape(orientation, actualpieceid);
		do{	//On scan la colomne jusqu'à ce qu'elle soit valide
			printf("Entrez la colonne: ");
			scanf("%c", &column);
		}while(letterConversion(column)<65 | letterConversion(column)>74-actualpiece.width+1);	//On vérifie si la pièce entre bien dans la grille de jeu
		column = column - 65;
		actualpiece.location = column;
		if (lost(grid, actualpiece) == 0){	//On place la pièce que si on ne perd pas en la plaçant
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
