#include "functions.h"

int fullLine(int* line){
	/*
	Role: Verify if a line of the grid game is full
	Inputs: 
		int* line: the line that we want to verify
	Output: 
		int: 1 if the line of full and 0 else
	*/
	if (line == NULL){
		printf("The line doesn't exist");
		exit(40);
	}
	int counter = 0;
	for (int i=0; i<SIDE; i++){
		if (line[i] == 1) counter++;
	}
	if (counter == SIDE) return 1;
	return 0;
}

void clearLine(int* line){
	/*
	Role: Clean a line with 0
	Inputs: 
		int* line: the line that we want to clean
	*/
	if (line == NULL){
		printf("The line doesn't exist");
		exit(40);
	}
	for (int i=0; i<SIDE; i++){
		line[i]=0;
	}
}

void cleaning(int** grid, int* score){
	/*
	Role: Clean the grid if some lines are full and calculate the score combo based on
	Inputs: 
		int** grid: the game grid
		int* score: the pointer of the actual game score
	*/
	if (grid == NULL){
		printf("The game grid is empty");
		exit(25);
	}
	if (score == NULL){
		printf("The score doesn't exist");
		exit(40);
	}
	int combo = 0;
	for (int i = SIDE-1; i>=0; i--){
		while (fullLine(grid[i])){
			clearLine(grid[i]);	//We clean the line
			combo++;
			for (int k = i; k>0; k--){	//We replace every line by its predecesor that we clean
				for (int j=0; j<SIDE; j++){
					grid[k][j]=grid[k-1][j];
				}
				clearLine(grid[k-1]);
			}
		}
	}
	actualscore(score, combo);
}

void actualscore(int* score, int combo){
	if (score == NULL){
		printf("The score doesn't exist");
		exit(40);
	}
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
	if (score == NULL){
		printf("The score doesn't exist");
		exit(40);
	}
	int copy;	//Copy character index from one file to another and the one to delete the temp file at the end
	int fscore = 1000000000;		//player score in board course for comparison
	char fname[50];		//name of the player in the course of the table for comparison, in itself it is useless it is just for the course
	char playername[50];	//Create player name for scores
	char reader[50];	//course variable for displaying highscores
	int highcounter = 0;	//variable to count the number of highscores when displaying
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
	
	printf("Vous avez perdu, entrez votre nom sans espace: ");
	scanf("%s", playername);	//player name scan
	printf("%s, votre score est de %d\n", playername, *score);	//Player name and score display
	
	//Copy of scores in temp then recopy taking into account the highscores
	rewind(scores);		
	while((copy=fgetc(scores))!=EOF){	//Copy to temp
		fputc(copy, temp);
	}
	rewind(scores);		//We return to the beginning of each file for the formatted copying
	rewind(temp);
	while (fscore>*score){	//scan the temporary file until the score of the player in the file is lower than that of the current player
		fscanf(temp, "%s %d", fname, &fscore);
		if (fscore>=*score){	//We only copy to the file if it is above the current score
			fprintf(scores, "%s %d\n", fname, fscore);
		}
	}
	fprintf(scores, "%s %d\n", playername, *score);	//write current score
	fprintf(scores, "%s %d\n", fname, fscore);	//We still write the last one that we didn't write because it was above
	while (fscanf(temp, "%s %d", fname, &fscore) != EOF){	//writing the rest of the scores
		fprintf(scores, "%s %d\n", fname, fscore);
	}
	printf("Highscores: \n");	//writing of the 5 best scores
	rewind(scores);
	while (fgets(reader, 50, scores) != NULL & highcounter  < 5){
		printf("%s", reader);
		highcounter++;
	}
	fclose(scores);
	fclose(temp);
	remove("temp.txt");	//Deleting the temporary file
}
