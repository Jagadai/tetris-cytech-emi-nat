#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIDE 10	//Taille de la grille en largeur et longueur

typedef struct{
	int** form;
	int location;
	int lenght;
	int width;
} piece;

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

void actualscore(int* score, int combo){	//calcul du score actuel en fonction des combos donnés par cleaning
	switch(combo){
		case 1:
			*score = *score+40;
			break;
		case 2:
			*score = *score+100;
			break;
		case 3:
			*score = *score+300;
			break;
		case 4:
			*score = *score+1200;
			break;
		default:
			break;
	}
}

int cleaning(int** grid){	//nettoyage des lignes pleines et calcul des lignes remplies pour le score
	int j, score;
	int regulation = 0, full=0;
	for (int i = SIDE-1; i>=0; i--){
		if (regulation >0){	//si la ligne est une copie de celle du dessus
			for(j=0;j<SIDE;j++){
				grid[i][j]=1;
			}
			regulation = regulation-1;	//régulation terminée
		}
		j=0;
		while (j<SIDE & grid[i][j] !=0){	//vérifier si la ligne est pleine
			j++;
		}
		if (j==SIDE-1){
			full = 1;
		}
		if (full){	//si elle est pleine on copie celle du dessus et on doit réguler cette situation
			for(j=0;j<SIDE;j++){
				grid[i][j]=grid[i-1][j];
			}
			regulation++;
		}
		
	}
	return score;
}
/*
int lost(int** grid){	//Vérification de fin de jeu
	int j=0, loser = 0;
	while (grid[0][j] == 0){	//parcours de la première ligne tant que vide
		j++;
	}
	if (j!=SIDE-1) loser = 1;	//si l'indice de parcours n'est pas égal à la taille de la ligne c'est perdu
	return loser;
}
*/
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

///////////////////////////////////////////////////////////////////////////////////////////////////
//PROCEDURE DE TEST
void randomGrid(int** grid){
	for(int i=0;i<SIDE;i++){	//remplissage random pour tests
		for(int j=0;j<SIDE;j++){
			grid[i][j]=rand()%2;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void initGrid(int** grid){
	for(int i=0;i<SIDE;i++){	//initialisation de toute la grille visible
		for(int j=0;j<SIDE;j++){
			grid[i][j]=0;
		}
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

piece adjustment(piece npiece){	//Ajuste la position de la pièce si elle est trop à droite
	while (npiece.location+npiece.width>SIDE){
		npiece.location--;
	}
	return npiece;
}

void placePiece(int** grid, piece npiece){	//à n'appeler que si lost = 0
	npiece = adjustment(npiece);	//Ajuste la pièce si trop à droite
	int depth = 1;	//La première ligne a déjà été vérifiée lors de lost, normalement elle est safe
	while (possiblePlacement(grid, npiece, depth) & (depth<SIDE-npiece.lenght)){	//Tant que pas de collision et que sol pas atteint on descend la pièce
		depth++;
	}
	if (depth<SIDE-npiece.lenght){	//On vérifie pourquoi on stop la descente, si c'est à cause du sol on remonte pas
		depth--; //On remonte d'un cran pour le placement
	}
	for(int i=0; i<npiece.lenght; i++){	//Place la pièce dans la grille
		for(int j=0; j<npiece.width; j++){
			grid[depth+i][npiece.location+j] = npiece.form[i][j];
		}
	}
}


int main(){
	srand(time(NULL));
	int* score;
	int** grid;
	score = malloc(sizeof(int));
	*score = 0;
	grid = malloc((SIDE)*sizeof(int*));	//Allocation des lignes du tableau
	if (grid == NULL){
		printf("Allocaion failure");
		exit(1);
	}
	for(int i=0;i<SIDE;i++){		//Allocation colonnes pour chaque ligne
		grid[i]=malloc(SIDE*sizeof(int));
		if (grid[i]==NULL){
			printf("Allocation failure");
			exit(2);
		}
	}
	
	
	/////////////////////////////////////////////////////////////////////
	//Test pour une piece
	piece carre;
	carre.form = malloc(2*sizeof(int*));
	for(int i=0; i<2; i++){
		carre.form[i] = malloc(2*sizeof(int));
	}
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			carre.form[i][j] = 1;
		}
	}
	carre.lenght = 2;
	carre.width = 2;
	carre.location = 2;
	//////////////////////////////////////////////////////////////////
	//Test pour le T
	int a,i,j;
	a=3;
	piece triangle;
	int **t;
	t=malloc(a*sizeof(int*));
	if(t==NULL){
		printf("malloc is bs\n");
		exit(1);
	}
	for(i=0;i<a;i++){
		t[i]=malloc(a*sizeof(int));
		if(t[i]==NULL){
			printf("malloc is bs\n");
			exit(1);
		}
			for(j=0;j<a;j++){
				t[i][j]=0;
			}
	}
	t[0][1]=1;
	for(i=0;i<a;i++){
		t[1][i]=1;
	}
	triangle.form = t;
	triangle.lenght = 2;
	triangle.width = 3;
	triangle.location = 6;


	//////////////////////////////////////////////////////////////////////
	initGrid(grid);
	//randomGrid(grid);
	
	display(grid);
	
	placePiece(grid, carre);
	display(grid);
	carre.location = 4;
	placePiece(grid, carre);
	display(grid);
	carre.location = 3;
	placePiece(grid, carre);
	display(grid);
	placePiece(grid, triangle);
	display(grid);
	
	free(grid);
	return 0;
}
