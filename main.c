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
	int time1;
	int time2;
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
		printf("Vous avez 10 secondes pour placer votre pièce\n");
		time1 = getTimeMicroSec();
		if (actualpieceid !=1){
			do{
				printf("Entrez l'orientation: ");
				scanf("%d", &orientation);
			}while(orientation<=0 | orientation>*nborientation);
		}
		printf("\n");
		printf("Entrez la lettre de la colonne: ");
		do{	//On scan la colomne jusqu'à ce qu'elle soit valide
			scanf("%c", &column);
		}while(letterConversion(column)<65 | letterConversion(column)>74-actualpiece.width+1); 	//On vérifie si la pièce entre bien dans la grille de jeu
		column = letterConversion(column) - 65;
		time2 = getTimeMicroSec();
		if (time2 - time1 >= 10000000){
			printf("Vous avez mis trop de temps pour répondre, la pièce est placée au hasard");
			actualpiece = finalshape(1+rand()%*nborientation, actualpieceid);
			actualpiece.location = rand()%10;
		}
		else{
			actualpiece = finalshape(orientation, actualpieceid);
			actualpiece.location = column;
		}
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
