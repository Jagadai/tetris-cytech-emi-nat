#include "functions.h"

int block(int* nborientation){
	/*
	Role: Select the actual block and determine how many orientations does it have
	Inputs: 
		int* nborientation: the pointer of the number of the piece's orientations
	Output: 
		int: The ID of the chossen block
	*/
	if (nborientation == NULL){
		printf("The nborientation pointer doesn't exist");
		exit(30);
	}
	int select,a;
	srand(time(NULL));
	select=1+rand()%7;
	switch(select){
		case 1:
			*nborientation = 1;
			return 1;	//choose square
			break;
		case 2:
			*nborientation = 4;
			return 2;	//choose t
			break;
		case 3:
			*nborientation = 2;
			return 3;	//choose I
			break;
		case 4:
			*nborientation = 4;
			return 4;	//choose L
			break;
		case 5:
			*nborientation = 4;
			return 5;	//choose J
			break;
		case 6:
			*nborientation = 2;
			return 6;	//choose S
			break;
		case 7:
			*nborientation = 2;
			return 7;	//choose Z
			break;
		default:
			printf("bad shape 1, %d",select);
			exit(31);
	}
}

void pieceCopy(int** piece1, int piece2[4][4], int lenght, int width){
	/*
	Role: Copy a piece from a fix array to an array defined with malloc
	Inputs: 
		int** piece1: the array defined with malloc
		int piece2[4][4]: the fix array
	*/
	if (piece1 == NULL){
		printf("The malloc array doesn't exist");
		exit(32);
	}
	for(int i =0; i<lenght; i++){
		for (int j =0; j<width; j++){
			piece1[i][j] = piece2[i][j];
		}
	}
}

piece finalshape(int orientation, int shapes){
	/*
	Role: Build the actual piece
	Inputs: 
		int orientation: The piece's orientation
		int shapes: the ID of the chossen piece
	Output: 
		piece actpiece: the piece build in an array
	*/
	piece actpiece;
	actpiece.form = malloc(4*sizeof(int*));
	for (int i=0; i<4; i++){
		actpiece.form[i]=malloc(4*sizeof(int));
	}
	switch(shapes){
		case 1:// carré
			actpiece.lenght = 2;
			actpiece.width = 2;
			int temppiece1[4][4] = {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
			pieceCopy(actpiece.form, temppiece1, actpiece.lenght, actpiece.width);
			break;
		case 2://T
			switch(orientation){
				case 1:
					actpiece.lenght = 2;
					actpiece.width = 3;
					int temppiece20[4][4] = {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
					pieceCopy(actpiece.form, temppiece20, actpiece.lenght, actpiece.width);
					break;
				case 2:
					actpiece.lenght = 2;
					actpiece.width = 3;
					int temppiece21[4][4] = {{1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
					pieceCopy(actpiece.form, temppiece21, actpiece.lenght, actpiece.width);
					break;
				case 3:
					actpiece.lenght = 3;
					actpiece.width = 2;
					int temppiece22[4][4] = {{1, 0, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}};
					pieceCopy(actpiece.form, temppiece22, actpiece.lenght, actpiece.width);
					break;
				case 4:
					actpiece.lenght = 3;
					actpiece.width = 2;
					int temppiece23[4][4] = {{0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}};
					pieceCopy(actpiece.form, temppiece23, actpiece.lenght, actpiece.width);
					break;
				default:
					printf("Bad orientation, %d", orientation);
					exit(330);
			}
			break;
		case 3://I
			switch(orientation){
				case 1:
					actpiece.lenght = 4;
					actpiece.width = 1;
					int temppiece30[4][4] = {{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}};
					pieceCopy(actpiece.form, temppiece30, actpiece.lenght, actpiece.width);
					break;
				case 2:
					actpiece.lenght = 1;
					actpiece.width = 4;
					int temppiece31[4][4] = {{1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
					pieceCopy(actpiece.form, temppiece31, actpiece.lenght, actpiece.width);
					break;
				default:
					printf("Bad orientation, %d", orientation);
					exit(331);
			}
			break;
		case 4://L
			switch(orientation){
				case 1:
					actpiece.lenght = 2;
					actpiece.width = 3;
					int temppiece40[4][4] = {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
					pieceCopy(actpiece.form, temppiece40, actpiece.lenght, actpiece.width);
					break;
				case 2:
					actpiece.lenght = 3;
					actpiece.width = 2;
					int temppiece41[4][4] = {{1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}};
					pieceCopy(actpiece.form, temppiece41, actpiece.lenght, actpiece.width);
					break;
				case 3:
					actpiece.lenght = 3;
					actpiece.width = 2;
					int temppiece42[4][4] = {{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}};
					pieceCopy(actpiece.form, temppiece42, actpiece.lenght, actpiece.width);
					break;
				case 4:
					actpiece.lenght = 2;
					actpiece.width = 3;
					int temppiece43[4][4] = {{1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
					pieceCopy(actpiece.form, temppiece43, actpiece.lenght, actpiece.width);
					break;
				default:
					printf("Bad orientation, %d", orientation);
					exit(332);
			}
			break;
		case 5://J
			switch(orientation){
				case 1:
					actpiece.lenght = 2;
					actpiece.width = 3;
					int temppiece50[4][4] = {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
					pieceCopy(actpiece.form, temppiece50, actpiece.lenght, actpiece.width);
					break;
				case 2:
					actpiece.lenght = 3;
					actpiece.width = 2;
					int temppiece51[4][4] = {{1, 1, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}};
					pieceCopy(actpiece.form, temppiece51, actpiece.lenght, actpiece.width);
					break;
				case 3:
					actpiece.lenght = 3;
					actpiece.width = 2;
					int temppiece52[4][4] = {{0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}};
					pieceCopy(actpiece.form, temppiece52, actpiece.lenght, actpiece.width);
					break;
				case 4:
					actpiece.lenght = 2;
					actpiece.width = 3;
					int temppiece53[4][4] = {{1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
					pieceCopy(actpiece.form, temppiece53, actpiece.lenght, actpiece.width);
					break;
				default:
					printf("Bad orientation, %d", orientation);
					exit(333);
			}
			break;
		case 6://s
			switch(orientation){
				case 1:
					actpiece.lenght = 2;
					actpiece.width = 3;
					int temppiece60[4][4] = {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
					pieceCopy(actpiece.form, temppiece60, actpiece.lenght, actpiece.width);
					break;
				case 2:
					actpiece.lenght = 3;
					actpiece.width = 2;
					int temppiece61[4][4] = {{1, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}};
					pieceCopy(actpiece.form, temppiece61, actpiece.lenght, actpiece.width);
					break;
				default:
					printf("Bad orientation, %d", orientation);
					exit(334);
			}
			break;
		case 7://z
			switch(orientation){
				case 1:
					actpiece.lenght = 2;
					actpiece.width = 3;
					int temppiece70[4][4] = {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
					pieceCopy(actpiece.form, temppiece70, actpiece.lenght, actpiece.width);
					break;
				case 2:
					actpiece.lenght = 3;
					actpiece.width = 2;
					int temppiece71[4][4] = {{0, 1, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}};
					pieceCopy(actpiece.form, temppiece71, actpiece.lenght, actpiece.width);
					break;
				default:
					printf("Bad orientation, %d", orientation);
					exit(335);
			}
			break;
		default:
			printf("bad shape 2, %d",shapes);
			exit(34);
	}
	return actpiece;
}

void displayPieceChoice(int pieceid){
	/*
	Role: Displays the choice of orientation for each piece
	Inputs: 
		int pieceid: the ID of the chossen piece
	*/
	switch(pieceid){
		case 1:
			printf("Voici la pièce à placer: \n@@\n@@\n");
			break;
		case 2:
			printf("1    2    3    4    \n @   @@@  @     @  \n@@@   @   @@   @@  \n          @     @  \n");
			break;
		case 3:
			printf("1    2    \n@    @@@@ \n@         \n@         \n@         \n");
				
			break;
		case 4:
			printf("1    2    3    4   \n  @  @@   @    @@@ \n@@@   @   @    @   \n      @   @@       \n");
			break;
		case 5:
			printf("1    2    3    4   \n@    @@    @   @@@ \n@@@  @     @     @ \n     @    @@       \n");
			break;
		case 6:
			printf("1    2  \n @@  @  \n@@   @@ \n      @ \n");
			break;
		case 7:
			printf("1    2  \n@@    @ \n @@  @@ \n     @  \n");
			break;
		default:
			printf("bad shape 3, %d",pieceid);
			exit(35);
	}
}
