all: exec

main.o: main.c functions.h
	gcc -c main.c -o main.o

basics.o: basics.c functions.h
	gcc -c basics.c -o basics.o

scores.o: scores.c functions.h
	gcc -c scores.c -o scores.o
	
piece.o: piece.c functions.h
	gcc -c piece.c -o piece.o

exec: main.o scores.o
	gcc main.o scores.o basics.o piece.o -o exec
