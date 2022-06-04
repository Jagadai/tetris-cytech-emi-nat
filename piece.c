#include<stdlib.h>
#include<stdio.h>
#include<time.h>

typedef struct{
int** form; //Le tableau contenant la pièce
int location; //L'emplacement de la colonne tout à gauche de la pièce
int lenght; //la hauteur de la pièce
int width; // la largeur de la pièce
}shape;

int block(){
	int select,a;
	srand(time(NULL));
	select=1+rand()%7;
	switch(select){
		case 1:
			return 1;	//choose square
			break;
		case 2:
			return 2;	//choose t
			break;
		case 3:
			return 3;	//choose I
			break;
		case 4:
			return 4;	//choose L
			break;
		case 5:
			return 5;	//choose J
			break;
		case 6:
			return 6;	//choose r
			break;
		case 7:
			return 7;	//choose z
			break;
		default:
			printf("bad shape, %d",select);
			exit(200);
	}
}

shape finalshape(int orientation, int shapes){
	int a,i,j;
	shape t;
	switch(shapes){
		case 1:			//square shape
			a=2;
			t.form=malloc(a*sizeof(int*));
			if(t.form==NULL){
				printf("malloc is bs\n");
				exit(1);
			}
			for(i=0;i<a;i++){
				t.form[i]=malloc(a*sizeof(int));
				if(t.form[i]==NULL){
					printf("malloc is bs\n");
					exit(1);
				}
				for(j=0;j<a;j++){
					t.form[i][j]=1;
				}
			}
			t.width=2;
			t.lenght=2;
			break;
		case 2:			//t shape
			a=3;
			t.form=malloc(a*sizeof(int*));
			if(t.form==NULL){
				printf("malloc is bs\n");
				exit(1);
			}
			for(i=0;i<a;i++){
				t.form[i]=malloc(a*sizeof(int));
				if(t.form[i]==NULL){
					printf("malloc is bs\n");
					exit(1);
				}
					for(j=0;j<a;j++){
						t.form[i][j]=0;	//everything to 0
					}
			}
			t.form[1][1]=1;				//we actually make the shape
			for(i=0;i<a;i++){
				t.form[2][i]=1;
			}
			t.width=3;
			t.lenght=2;
			break;		//and we do the same thing for every shape
		case 3:			//I shape
			a=4;
			t.form=malloc(a*sizeof(int*));
			if(t.form==NULL){
				printf("malloc is bs\n");
				exit(1);
			}
			for(i=0;i<a;i++){
				t.form[i]=malloc(a*sizeof(int));
				if(t.form[i]==NULL){
					printf("malloc is bs\n");
					exit(1);
				}
					for(j=0;j<a;j++){
						t.form[i][j]=0;
					}
			}
			for(i=0;i<a;i++){
				t.form[3][i]=1;
			}
			t.width=4;
			t.lenght=1;
			break;
		case 4:			//L shape
			a=3;
			t.form=malloc(a*sizeof(int*));
			if(t.form==NULL){
				printf("malloc is bs\n");
				exit(1);
			}
			for(i=0;i<a;i++){
				t.form[i]=malloc(a*sizeof(int));
				if(t.form[i]==NULL){
					printf("malloc is bs\n");
					exit(1);
				}
					for(j=0;j<a;j++){
						t.form[i][j]=0;
					}
			}
			t.form[1][2]=1;
			for(i=0;i<a;i++){
				t.form[2][i]=1;
			}
			t.width=3;
			t.lenght=2;
			break;
		case 5:			//J shape
			a=3;
			t.form=malloc(a*sizeof(int*));
			if(t.form==NULL){
				printf("malloc is bs\n");
				exit(1);
			}
			for(i=0;i<a;i++){
				t.form[i]=malloc(a*sizeof(int));
				if(t.form[i]==NULL){
					printf("malloc is bs\n");
					exit(1);
				}
					for(j=0;j<a;j++){
						t.form[i][j]=0;
					}
			}
			t.form[1][0]=1;
			for(i=0;i<a;i++){
				t.form[2][i]=1;
			}
			t.width=3;
			t.lenght=2;
			break;
		case 6:			//r shape
			a=3;
			t.form=malloc(a*sizeof(int*));
			if(t.form==NULL){
				printf("malloc is bs\n");
				exit(1);
			}
			for(i=0;i<a;i++){
				t.form[i]=malloc(a*sizeof(int));
				if(t.form[i]==NULL){
					printf("malloc is bs\n");
					exit(1);
				}
					for(j=0;j<a;j++){
						t.form[i][j]=0;
					}
			}
			for(i=0;i<2;i++){
				t.form[2][i]=1;
			}
			for(i=0;i<2;i++){
				t.form[1][i+1]=1;
			}
			t.width=3;
			t.lenght=2;
			break;
		case 7:			//z shape
			a=3;
			t.form=malloc(a*sizeof(int*));
			if(t.form==NULL){
				printf("malloc is bs\n");
				exit(1);
			}
			for(i=0;i<a;i++){
				t.form[i]=malloc(a*sizeof(int));
				if(t.form[i]==NULL){
					printf("malloc is bs\n");
					exit(1);
				}
					for(j=0;j<a;j++){
						t.form[i][j]=0;
					}
			}
			for(i=0;i<2;i++){
				t.form[2][i+1]=1;
			}
			for(i=0;i<2;i++){
				t.form[1][i]=1;
			}
			t.width=3;
			t.lenght=2;
			break;



		default:
			printf("shape #%d not handled yet\n",shapes);
			exit(200);
	}	
	return t;
}

int main(){
	int rb,or,i;
	shape ns;
	rb=block();	//choose a random shape
	or=1;
	ns=finalshape(or,rb);
	/*for(i=0;i<4;i++){
		if(ns.form[i][0]==){
			ns.width=i;
			exit(2);
		}
	}
	for(i=0;i<4;i++){
		if(ns.form[0][i]==){
			ns.lenght=i;
			exit(2);
		}
	}*/
	
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			printf("%d",ns.form[i][j]);
		}
	printf("\n");
	}
	printf("%d the width\n",ns.width);
	printf("%d the length\n",ns.lenght);
	free(ns.form);
}
