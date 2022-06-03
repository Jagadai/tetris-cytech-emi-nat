#include<stdlib.h>
#include<stdio.h>
#include<time.h>

typedef struct{
	int orientation;
	int shape;
}piece;

int block(){
	int select,a;
	srand(time(NULL));
	select=1+rand()%7;
	switch(select){
		case 1:
			return 1;
			break;
		case 2:
			return 2;
			break;
		case 3:
			return 3;
			break;
		case 4:
			return 4;
			break;
		case 5:
			return 5;
			break;
		case 6:
			return 6;
			break;
		case 7:
			return 7;
			break;
		default:
			printf("bad shape, %d",select);
			exit(200);
	}
}

int** finalshape(int orientation, int shape){
	int a,i,j;
	int **t;
	switch(shape){
		case 1:			//square shape
			a=2;
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
					t[i][j]=1;
				}
			}
			break;
		case 2:			//t shape
			a=3;
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
			break;



		default:
			printf("shape #%d not handled yet\n",shape);
			exit(200);
	}	
	return t;
}

int main(){
	int rb,or;
	int **ns;
	rb=block();	//choose a random shape
	or=1;
	ns=finalshape(or,rb);
	/*for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			printf("%d",ns[i][j]);
		}
	printf("\n");
	}*/
	free(ns);
}






