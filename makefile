all : main 

glouton.o : glouton.c glouton.h genpoly.h
	gcc -o glouton.o -c glouton.c -Wall -lm -lSDL


essai.o : essai.c essai.h genpoly.h
	gcc -o essai.o -c essai.c -Wall -lm 



main : main.c graphique.h graphique.c genpoly.c genpoly.h glouton.o essai.o dynamique.c dynamique.h
	gcc -o main main.c graphique.c genpoly.c glouton.o essai.o -Wall -lm -lSDL


clean:
	rm -f main
	rm -f glouton
	rm -f essai
	rm -f *.o *.s *.i *.so *~
