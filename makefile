all : main 

glouton.o : glouton.c glouton.h main.h genpoly.h
	gcc -o glouton.o -c glouton.c -Wall -lm -lSDL





main : main.c graphique.h graphique.c genpoly.c genpoly.h glouton.o essai.h essai.c dynamique.c dynamique.h
	gcc -o main main.c graphique.c genpoly.c glouton.o -Wall -lm -lSDL


clean:
	rm -f main
	rm -f glouton
	rm -f *.o *.s *.i *.so *~
