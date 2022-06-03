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


int fullLine(int* line){	//vérifie si une ligne est pleine
	int counter = 0;
	for (int i=0; i<SIDE; i++){
		if (line[i] == 1) counter++;
	}
	if (counter == SIDE) return 1;
	return 0;
}

void clearLine(int* line){	//nettoie une ligne
	for (int i=0; i<SIDE; i++){
		line[i]=0;
	}
}

void cleaning(int** grid, int* score){	//nettoyage des lignes pleines et calcul des lignes remplies pour le score
	int combo = 0;
	for (int i = SIDE-1; i>=0; i--){
		while (fullLine(grid[i])){
			clearLine(grid[i]);	//On nettoie la ligne
			combo++;
			for (int k = i; k>0; k--){	//On remplace chaque ligne par sa précédente que l'on nettoie
				for (int j=0; j<SIDE; j++){
					grid[k][j]=grid[k-1][j];
				}
				clearLine(grid[k-1]);
			}
		}
	}
	actualscore(score, combo);
	
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

void scoreSave(int* score){
	int copy;	//Indice de caractère de copie d'un fichier à l'autre
	int fscore = 100000000;		//score du joueur dans le parcours du tableau pour comparaison
	char fname[50];		//nom du joueur dans le parcours du tableau pour comparaison, en soit il sert à rien c'est juste pour le parcours
	char playername[50];	//Création nom du joueur pour scores
	FILE* scores = NULL;
	FILE* temp = NULL;
	scores = fopen("scores.txt", "r+");
	temp = fopen("temp.txt", "r+");
	if (scores == NULL){
		printf("Ouverture du fichier impossible\n");
		printf("code d'erreur: %d \n", errno);
		printf("Message d'erreur: %s \n", strerror(errno));
		exit(3);
	}
	if (temp == NULL){
		printf("Ouverture du fichier impossible\n");
		printf("code d'erreur: %d \n", errno);
		printf("Message d'erreur: %s \n", strerror(errno));
		exit(4);
	}
	
	printf("Entrez votre nom: ");
	scanf("%s", playername);	//scan du nom du joueur
	printf("%s, votre score est de %d\n", playername, *score);	//Affichage nom du joueur et score
	
	//Copie de scores dans temp puis recopie en tenant compte des highscores
	rewind(scores);		
	while((copy=fgetc(scores))!=EOF){	//Copie dans temp
		fputc(copy, temp);
	}
	rewind(scores);		//On revient au début de chaque fichier pour le recopiage mis en forme
	rewind(temp);
	while (fscore>=*score){	//scan du fichier temporaire jusqu'à ce que le score du joueur du fichier soit plus faible que celui du joueur actuel
		fscanf(temp, "%s %d", fname, &fscore);
		if (fscore>=*score){	//On ne copie dans le fichier que si c'est au dessus du score actuel
			fprintf(scores, "%s %d\n", fname, fscore);
		}
	}
	fprintf(scores, "%s %d\n", playername, *score);	//écriture du score actuel
	fprintf(scores, "%s %d\n", fname, fscore);	//On écrit quand même le dernier qu'on a pas écrit parce qu'il était au dessus
	while (fscanf(temp, "%s %d", fname, &fscore) != EOF){	//écriture du reste des scores
		fprintf(scores, "%s %d\n", fname, fscore);
	}
	printf("Highscores: \n");
	rewind(scores);
	char reader[50];
	int highcounter = 0;
	while (fgets(reader, 50, scores) != NULL & highcounter  < 5){
		printf("%s", reader);
		highcounter++;
	}
	fclose(scores);
	fclose(temp);
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
			exit(2);
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
	
	
	display(grid);
	placePiece(grid, carre);
	display(grid);
	carre.location = 4;
	placePiece(grid, carre);
	display(grid);
	carre.location = 3;
	placePiece(grid, carre);
	display(grid);
	//placePiece(grid, triangle);
	//display(grid);
	carre.location = 0;
	placePiece(grid, carre);
	display(grid);
	carre.location = 6;
	placePiece(grid, carre);
	display(grid);
	carre.location = 8;
	placePiece(grid, carre);
	display(grid);
	cleaning(grid, score);
	display(grid);
	
	scoreSave(score);
	
	free(score);
	free(grid);
	return 0;
}
