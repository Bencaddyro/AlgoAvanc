#include <stdio.h>
#include <stdlib.h>
#include "dynamique.h"
#include "genpoly.h"


void print_piou(piou P){
	int i = 0;
	printf("____________________________________________________________________________________\n");
	printf("somme corde = %d \n", P.somme_corde);
	printf("nb cordes = %d \n", P.nb_corde);
	printf("Tableau de corde \n");
	for (i = 0; i < P.nb_corde; i++){
		printf("corde %d \n", i);
		printf("point 1 : x = %d , y = %d , lon = %f \n", P.tab_corde[i].p1.x, P.tab_corde[i].p1.y, P.tab_corde[i].lon);
		printf("point 2 : x = %d , y = %d , lon = %f \n", P.tab_corde[i].p2.x, P.tab_corde[i].p2.y, P.tab_corde[i].lon);
	}
	printf("____________________________________________________________________________________\n");
}

/*
typedef struct{
	int somme_corde; //Somme de toutes les cordes ajoutées 
	int nb_corde;	//Nombres totales de cordes dans le sous-polygone observé
	corde tab_corde[nb_corde];	//Tableau contenant toutes les cordes retenues
} piou;*/


/*
typedef struct{
  int x;
  int y;
} point;


typedef struct{
  point p1;
  point p2;
  float lon;
} corde2;

*/


/*Remarque, voici ce à quoi ressemble tab_sous_poly

	_| 2 | 3 | 4 | 0 | 1
	0|
	1|
	2|
	3|
	4|
	

*/



void soldynamique(int n,point poly[],corde2 solution[]){
	piou tab_sous_poly[n][n];	//On ne remplira que le triangle suppérieur. 
	int i,j,k,l,t,x,y;
	int x1, y1;
	int NB_sommets =3; //Correspond au nombre de sommets du sous-polygone (au minimum 4)

	x1=0; y1=0;

	//Initialisation de tab_sous_poly
	//printf("DEBUT INITIALISATION  \n");
	for(i = 0; i < n ; i++){
		//printf("i = %d \n",i);
		corde2 c;	//Création de la corde
		if(i < n - 2){
			c.p1 = poly[i];
			c.p2 = poly[i+2];
		}
		//Attention pour le tracer des 2 derniéres cordes (Sn-1,S0) et (Sn,S1) d'ou le if
		if(i == n - 2){
			c.p1 = poly[i];
			c.p2 = poly[0]; 
		}
		if(i == n - 1){
			c.p1 = poly[i];
			c.p2 = poly[1]; 
		}
		c.lon = coutcorde2(c);
		//1ère diagonale du tableau
		tab_sous_poly[i][i].somme_corde = c.lon;
		tab_sous_poly[i][i].nb_corde = 1; //On ne regarde qu'une seule corde à cette étape
		tab_sous_poly[i][i].tab_corde = malloc(1*sizeof(corde2));
		tab_sous_poly[i][i].tab_corde[0] = c ;
		//print_piou(tab_sous_poly[i][i]);
	}
	//printf("FIN INITIALISATION \n");
	
	printf("DEBUT PARCOURS TABLEAU \n");
	int increment = 2;
	for(j = 1; j < n-2; j++){	
		NB_sommets ++;
		increment ++;
		for(i = 0; i < (n - j - 1); i++){
			t = j + i;
			//printf("Création de la corde  \n");
			//Création de la corde 
				corde2 c;
				if ( t < n - 2){
					c.p1 = poly[i];
					c.p2 = poly[i + increment];
				}
				if ( t == n - 2){
					c.p1 = poly[i];
					c.p2 = poly[0];
				} 
				if ( t == n - 1){
					c.p1 = poly[i];
					c.p2 = poly[1];
				} 
				c.lon = coutcorde2(c);


			
			//printf("Recherche \n");
			// Coordonées x,y utilsées pour garder en mémoir la meilleur case du tableau
			x = i;	
			y = t-1;
			int somme_corde_min = tab_sous_poly[x][y].somme_corde + c.lon;
			int somme_corde_2 = 0 ;


		
			//Attention quand 4 sommets on regarde que 2 cordes 
			if(NB_sommets == 4 ){
				somme_corde_2 = tab_sous_poly[i+1][t].somme_corde + c.lon;
				if ( somme_corde_2 < somme_corde_min){
					somme_corde_min = somme_corde_2;
					//ATTENTION on "inverse" x et y pour le tableau au lieu de regarder (1,2) on va regarder (2,1)
					x = i+1;
					y = t;
				}
			}


			printf("nb sommets %d \n", NB_sommets);


			//PLus de 4 sommets
				if(NB_sommets > 4){

				somme_corde_2 = tab_sous_poly[i+1][t-1].somme_corde + c.lon;
				if ( somme_corde_2 < somme_corde_min){
					somme_corde_min = somme_corde_2;
						x = i+1;
						y = t-1;
				}

				if(NB_sommets > 5){
					for(k = 2 ; k <= NB_sommets - 3; k++){	
						somme_corde_2 = tab_sous_poly[i][k+1].somme_corde + tab_sous_poly[i+k][t-k].somme_corde + c.lon;
						printf("somme corde=%d     somme corde 2=%d \n", somme_corde_min, somme_corde_2);
						if ( somme_corde_2 < somme_corde_min){
							somme_corde_min = somme_corde_2;
							//Même remarque que au dessus pour le tableau et x,y
							printf("x=%d     y=%d  x1=%d y1=%d \n", x,y,x1,y1);
							x = i;
							y = k + 1 - 2;
							x1 = i + k;
							y1 = NB_sommets - k - 2;
							printf("x=%d     y=%d  x1=%d y1=%d \n", x,y,x1,y1);
						}
					}
				}
			}


			//printf("Fin recherche \n");




			//printf("corde A AJOUTER", i);
		//printf("point 1 : x = %d , y = %d , lon = %f \n", c.p1.x, c.p1.y, c.lon);
		//printf("point 2 : x = %d , y = %d , lon = %f \n", c.p2.x, c.p2.y, c.lon);
			
			printf("Ajout de la corde  \n");
			//Enregistrement dans notre tableau de corde
			int ArraySize;
			printf("j = %d \n", j);
			printf("i = %d \n", i);
			printf("t = %d \n", j+i);

			tab_sous_poly[i][t].somme_corde = somme_corde_min;
			tab_sous_poly[i][t].nb_corde = tab_sous_poly[x][y].nb_corde + 1; //le +1 est pour la nouvelle corde ajoutée
			ArraySize = tab_sous_poly[i][t].nb_corde;
			printf("x = %d , y = %d \n", x,y);
			tab_sous_poly[i][t].tab_corde = malloc(ArraySize*sizeof(corde2));
			if (tab_sous_poly[i][t].tab_corde == NULL) {
  				fprintf(stderr, "malloc failed\n");
 				 //return(-1);
			}

			//printf("Cordes à enregister = %d x=%d y=%d \n",tab_sous_poly[x][y].nb_corde,x,y);
			//print_piou(tab_sous_poly[x][y]);
			printf("Cordes tot = %d \n",ArraySize);
			//Enregistrement du tableau de corde 
			for(l = 0; l < (ArraySize - 1); l++){
				//printf("l = %d \n",l);
				//printf("x= %d y=%d \n",x,y);
				//printf("som(j,j+i) = %d som_min= %d \n",tab_sous_poly[i][t].somme_corde, somme_corde_min);
				tab_sous_poly[i][t].tab_corde[l] = tab_sous_poly[x][y].tab_corde[l] ;
			}
			
			//printf("suite \n");
			//Enregistrement de la corde c
			tab_sous_poly[i][t].tab_corde[ArraySize-1] = c  ;
			print_piou(tab_sous_poly[i][t]);
			//Cas ou on doit enregistrer deux tableaux de cordes et non pas un seul
			if ( x1 != 0 && y1 != 0){
				printf("Ajout de 2 tableau de corde \n");
				int NewSize;	// Taille lors de l'aggrandissement du tableau
				tab_sous_poly[i][t].nb_corde += tab_sous_poly[x1][y1].nb_corde;
				NewSize = tab_sous_poly[i][t].nb_corde ; 
				//On réaloue de l'espace pour le tableau
				tab_sous_poly[i][t].tab_corde = realloc (tab_sous_poly[i][t].tab_corde, (NewSize) * sizeof (corde2));
				for (l = ArraySize; l < NewSize; l++){
 					tab_sous_poly[i][t].tab_corde[l] = tab_sous_poly[x1][y1].tab_corde[l - ArraySize];
				}
				x1 = 0;
				y1 = 0;
				print_piou(tab_sous_poly[i][t]);
			}

						
		}		
	}
	if ( tab_sous_poly[0][n-2].somme_corde < tab_sous_poly[1][n - 1].somme_corde){
		x = 0;
		y = n -4;
	}
	else{
		x = 1;
		y = n - 3;
	}

	
	printf("ENREGISTREMENT SOLUTION FINAL \n");
	printf("x=%d y=%d \n",x,y);
	//On enregistre la solution dans le tableau de solution
	for (i = 0; i < tab_sous_poly[x][y].nb_corde; i++){
		solution[i] = tab_sous_poly[x][y].tab_corde[i];
		printf(" i = %d \n",i);
	}
	print_piou(tab_sous_poly[x][y]);

	printf("Fin  enregistrement\n");
	/*for ( i = 0; i < n - 2; i++){
		for ( j = i; j < n - i; j++){
			free(tab_sous_poly[i][j].tab_corde);
		} 
	}*/

	printf("Fin  \n");
}





