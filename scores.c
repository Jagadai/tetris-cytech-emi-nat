#include "functions.h"

int fullLine(int* line){	//vérifie si une ligne est pleine
	/*
	Role: Verify if a line of the grid game is full
	Inputs: 
		int* line: the line that we want to verify
	Output: 
		int: 1 if the line of full and 0 else
	*/
	int counter = 0;
	for (int i=0; i<SIDE; i++){
		if (line[i] == 1) counter++;
	}
	if (counter == SIDE) return 1;
	return 0;
}

void clearLine(int* line){	//nettoie une ligne
	/*
	Role: Clean a line with 0
	Inputs: 
		int* line: the line that we want to clean
	*/
	for (int i=0; i<SIDE; i++){
		line[i]=0;
	}
}

void cleaning(int** grid, int* score){	//nettoyage des lignes pleines et calcul des lignes remplies pour le score
	/*
	Role: Clean the grid if some lines are full and calculate the score combo based on
	Inputs: 
		int** grid: the game grid
		int* score: the pointer of the actual game score
	*/
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

void actualscore(int* score, int combo){	//calcul du score actuel en fonction des combos donnés par cleaning
	/*
	Role: Calculate the points of each combo and add it to the score
	Inputs: 
		int* score: the pointer of the actual game score
		int combo: the combo made by the player
	*/
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

void scoreSave(int* score){
	/*
	Role: Put the score in a text file and displays the highscores at the end of the game
	Inputs: 
		int* score: the actual game score
	*/
	int copy;	//Indice de caractère de copie d'un fichier à l'autre et celui pour supprimer le fichier temp à la fin
	int fscore = 1000000000;		//score du joueur dans le parcours du tableau pour comparaison
	char fname[50];		//nom du joueur dans le parcours du tableau pour comparaison, en soit il sert à rien c'est juste pour le parcours
	char playername[50];	//Création nom du joueur pour scores
	char reader[50];	//variable de parcours pour affichage highscores
	int highcounter = 0;	//variable pour compter le nombre de highscores lors de l'affichage
	FILE* scores = NULL;
	FILE* temp = NULL;
	scores = fopen("scores.txt", "r+");
	temp = fopen("temp.txt", "w+");
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
	
	printf("Vous avez perdu, e ntrez votre nom sans espace: ");
	scanf("%s", playername);	//scan du nom du joueur
	printf("%s, votre score est de %d\n", playername, *score);	//Affichage nom du joueur et score
	
	//Copie de scores dans temp puis recopie en tenant compte des highscores
	rewind(scores);		
	while((copy=fgetc(scores))!=EOF){	//Copie dans temp
		fputc(copy, temp);
	}
	rewind(scores);		//On revient au début de chaque fichier pour le recopiage mis en forme
	rewind(temp);
	while (fscore>*score){	//scan du fichier temporaire jusqu'à ce que le score du joueur du fichier soit plus faible que celui du joueur actuel
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
	printf("Highscores: \n");	//écriture des 5 meilleurs scores
	rewind(scores);
	while (fgets(reader, 50, scores) != NULL & highcounter  < 5){
		printf("%s", reader);
		highcounter++;
	}
	fclose(scores);
	fclose(temp);
	remove("temp.txt");	//Suppression du fichier temporaire
}
