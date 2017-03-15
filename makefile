all : main






main : main.c graphique.h graphique.c genpoly.c genpoly.h
	gcc -o main main.c graphique.c genpoly.c -Wall -lm -lSDL
