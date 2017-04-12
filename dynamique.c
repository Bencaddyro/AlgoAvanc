#include <stdio.h>
#include <stdlib.h>
#include "dynamique.h"
#include "genpoly.h"

void soldynamique(int n,point poly[],corde2 solution[]){
	//int s_deb, s_fin;	//Représentes les sommets de débuts et de fin des sous-polygonnes étudié 
	//int taille = n+2;	//Longeur du tableau tab_sous_poly	
	piou tab_sous_poly[n][n];	//On ne remplira que le triangle suppérieur. 
	int i,j,k,l;
	int x1, y1 = 0;

	//Initialisation de tab_sous_poly
	printf("Debut Initialisation \n");
	for(i = 0; i < n; i++){
		//Création de la corde
		corde2 c;
		c.p1 = poly[i];
		c.p2 = poly[i+2];
		c.lon = coutcorde2(c);
		//1ère diagonale du tableau
		tab_sous_poly[i][i].somme_corde = c.lon;
		tab_sous_poly[i][i].nb_corde = 1; //On ne regarde qu'une seule corde à cette étape
		tab_sous_poly[i][i].tab_corde = malloc(1*sizeof(corde2));
		tab_sous_poly[i][i].tab_corde[0] = c ;
		//Attention pour le tracer des 2 derniéres cordes (Sn-1,S0) et (Sn,S1) d'ou le if
		if(i >= n - 2){
			corde2 c;
			c.p1 = poly[i];
			c.p2 = poly[n-2-i]; 
			c.lon = coutcorde2(c);
			//1ère diagonale du tableau
			tab_sous_poly[i][i].somme_corde = c.lon;
			tab_sous_poly[i][i].nb_corde = 1; //On ne regarde qu'une seule corde à cette étape
			tab_sous_poly[i][i].tab_corde = malloc(1*sizeof(corde2));
			tab_sous_poly[i][i].tab_corde[0] = c ;
		}
	}
	printf("Fin Initialisation \n");
	
	printf("Debut Parcourts Tableau \n");
	for(i = 1; i < n; i++){
		for(j = 0; j < (n - i); j++){
			printf("Création de la corde \n");
			//Création de la corde 
			corde2 c;
			c.p1 = poly[j];
			c.p2 = poly[j+i];
			c.lon = coutcorde2(c);
			
			printf("Recherche \n");
			int NB_sommets = i + 1; //Correspond au nombre de sommets du sous-polygone
			// Coordonées x,y utilsées pour garder en mémoir la meilleur case du tableau
			int x = j;	
			int y = j+i-1;
			int somme_corde_min = tab_sous_poly[x][y].somme_corde + c.lon;
		
			//Attention quand 4 sommets on regarde que 2 cordes 
			int somme_corde_2 = tab_sous_poly[j+1][j+i-1].somme_corde + c.lon;
			if ( somme_corde_2 < somme_corde_min){
				somme_corde_min = somme_corde_2;
				x = j+1;
				y = j+i-1;
			}

			//PLus de 4 sommets
			if(NB_sommets > 4){
				//int x1 = j;	
				//int y1 = 3;	//k+1 avec k=2
				//int x2 = j + 2;
				//int y2 = NB_sommets - 2;
				for(k = 2 ; k <= NB_sommets - 3; k++){	
					int somme_corde_2 = tab_sous_poly[j][k+1].somme_corde + tab_sous_poly[j+k][NB_sommets-k].somme_corde + c.lon;
					if ( somme_corde_2 < somme_corde_min){
						somme_corde_min = somme_corde_2;
						x = j;
						y = k+1;
						x1 = j+k;
						y1 = NB_sommets-k;
					}
				}
			}
			printf("Fin recherche \n");
			
			printf("Ajout de la corde \n");
			//Enregistrement dans notre tableau de corde
			int ArraySize;
			printf("j = %d \n", j);
			printf("i = %d \n", i);
			printf("j + i = %d \n", j+i);

			tab_sous_poly[j][j+i].somme_corde = somme_corde_min;
			tab_sous_poly[j][j+i].nb_corde = tab_sous_poly[x][y].nb_corde + 1; //le +1 est pour la nouvelle corde ajoutée
			ArraySize = tab_sous_poly[j][j+i].nb_corde;
			tab_sous_poly[i][j+i].tab_corde = malloc(ArraySize*sizeof(corde2));
			printf("taille = %d \n", ArraySize);

			//Enregistrement du tableau de corde 
			for(l = 0; l < ArraySize - 1; l++){
				printf("l = %d \n",l);
				printf("x= %d y=%d \n",x,y);
				printf("som(j,j+i) = %d som_min= %d \n",tab_sous_poly[j][j+i].somme_corde, somme_corde_min);
				tab_sous_poly[j][j+i].tab_corde[l] = tab_sous_poly[x][y].tab_corde[l] ;
			}
			
			//Enregistrement de la corde c
			tab_sous_poly[j][j+i].tab_corde[ArraySize-1] = c  ;

			//Cas ou on doit enregistrer deux tableaux de cordes et non pas un seul
			if ( x1 != 0 && y1 != 0){
				printf("Ajout de 2 tableau de corde \n");
				int NewSize;	// Taille lors de l'aggrandissement du tableau
				tab_sous_poly[j][j+i].nb_corde += tab_sous_poly[x1][y1].nb_corde;
				NewSize = tab_sous_poly[j][j+i].nb_corde ; 
				//On réaloue de l'espace pour le tableau
				tab_sous_poly[j][j+i].tab_corde = realloc (tab_sous_poly[j][j+i].tab_corde, (NewSize) * sizeof (corde2));
				for (l = ArraySize; l < NewSize; l++){
 					tab_sous_poly[j][j+i].tab_corde[l] = tab_sous_poly[x1][y1].tab_corde[l - ArraySize];
				}
			}

						
		}		
	}
	
	printf("Fin \n");
	//On enregistre la solution dans le tableau de solution
	for (i = 0; i < tab_sous_poly[n-1][n-1].nb_corde; i++){
		solution[i] = tab_sous_poly[n-1][n-1].tab_corde[i];
	}
}



/*
typedef struct{
	int somme_corde; //Somme de toutes les cordes ajoutées 
	int nb_corde;	//Nombres totales de cordes dans le sous-polygone observé
	corde tab_corde[nb_corde];	//Tableau contenant toutes les cordes retenues
} piou;*/


/*Remarque, voici ce à quoi ressemble tab_sous_poly

	_| 2 | 3 | 4 | 0 | 1
	0|
	1|
	2|
	3|
	4|
	

*/


