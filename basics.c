#include "functions.h"

unsigned long getTimeMicroSec(){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (1000000 * tv.tv_sec) + tv.tv_usec;
}

char box(int p){	//affichage de chaque case
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

void display(int** grid){	//Affichage du jeu
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
	for(int i=0;i<SIDE;i++){	//initialisation de toute la grille
		for(int j=0;j<SIDE;j++){
			grid[i][j]=0;
		}
	}
	for(int j=0;j<SIDE;j++){
		grid[SIDE][j]=1;
	}
}

int possiblePlacement(int** grid, piece npiece, int depth){
	for(int i=0; i<npiece.lenght; i++){	//Vérifie si on peut placer la pièce à cet endroit
		for(int j=0; j<npiece.width; j++){
			if (npiece.form[i][j] == grid[depth+i][npiece.location + j] & npiece.form[i][j] == 1){
				return 0;
			}
		}
	}
	return 1;
}
int lost(int** grid, piece npiece){	//vérifie si l'on a perdu en essayant de placer la pièce tout en haut de l'endroit indiqué par le user
	if (possiblePlacement(grid, npiece, 0) == 0) return 1;
	return 0;
}

void placePiece(int** grid, piece npiece){	//à n'appeler que si lost = 0
	int depth = 1;	//La première ligne a déjà été vérifiée lors de lost, normalement elle est safe
	while (possiblePlacement(grid, npiece, depth)){	//Tant que pas de collision et que sol pas atteint on descend la pièce
		depth++;
	}
	depth--; //On remonte d'un cran pour le placement
	for(int i=0; i<npiece.lenght; i++){	//Place la pièce dans la grille
		for(int j=0; j<npiece.width; j++){
			if (npiece.form[i][j] == 1){ //On ne copie que si c'est une case pleine
				grid[depth+i][npiece.location+j] = npiece.form[i][j];
			}
		}
	}
}

int letterConversion(char letter){	//convertie la lettre de la colonne si passée en minuscule
	if (letter<107 & letter>96){
		letter-= 32;
	}
	return letter;
}
