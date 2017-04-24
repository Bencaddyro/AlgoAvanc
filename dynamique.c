#include <stdio.h>
#include <stdlib.h>
#include "dynamique.h"
#include "genpoly.h"


void print_piou(piou P){
	int i = 0;
	printf("somme corde = %d \n", P.somme_corde);
	printf("nb cordes = %d \n", P.nb_corde);
	printf("Tableau de corde \n");
	for (i = 0; i < P.nb_corde; i++){
		printf("corde %d \n", i);
		printf("point 1 : x = %d , y = %d , lon = %f \n", P.tab_corde[i].p1.x, P.tab_corde[i].p1.y, P.tab_corde[i].lon);
		printf("point 2 : x = %d , y = %d , lon = %f \n", P.tab_corde[i].p2.x, P.tab_corde[i].p2.y, P.tab_corde[i].lon);
	}
}




/*Remarque, voici ce à quoi ressemble tab_sous_poly

	_| 2 | 3 | 4 |
	0|
	1|
	2|
	

*/



void soldynamique(int n,point poly[],corde2 solution[]){
	piou tab_sous_poly[n-2][n-2];	//On ne remplira que le triangle suppérieur. 
	int i,j,k,l,t,x,y;
	int ArraySize;
	int NB_sommets =3; //Correspond au nombre de sommets du sous-polygone (au minimum 4)
	int x1 = -1;
	int y1 = -1;
	int suite = 0;

	x1=0; y1=0;

	//Initialisation de tab_sous_poly
	for(i=0; i<n-2; i++){
		for(j=0;j<n-2; j++){
			tab_sous_poly[i][j].tab_corde = NULL;
		}
	}

	//printf("DEBUT INITIALISATION  \n");
	for(i = 0; i < n-2 ; i++){
		//printf("i = %d \n",i);
		corde2 c;	//Création de la corde
		c.p1 = poly[i];
		c.p2 = poly[i+2];
		//Attention pour le tracer des 2 derniéres cordes (Sn-1,S0) et (Sn,S1) d'ou le if
		/*if(i == n - 2){
			c.p1 = poly[i];
			c.p2 = poly[0]; 
		}
		if(i == n - 1){
			c.p1 = poly[i];
			c.p2 = poly[1]; 
		}*/
		c.lon = coutcorde2(c);
		//1ère diagonale du tableau
		tab_sous_poly[i][i].somme_corde = c.lon;
		tab_sous_poly[i][i].nb_corde = 1; //On ne regarde qu'une seule corde à cette étape
		tab_sous_poly[i][i].tab_corde = malloc(1*sizeof(corde2));
		tab_sous_poly[i][i].tab_corde[0] = c ;
		print_piou(tab_sous_poly[i][i]);
	}
	//printf("FIN INITIALISATION \n");
	
	printf("DEBUT PARCOURS TABLEAU \n");
	int increment = 2;
	int save;
	for(j = 1; j < n-3; j++){	
		NB_sommets ++;
		increment ++;
		save = NB_sommets;
		for(i = 0; i < (n - j - 2); i++){
			t = j + i;
			//printf("Création de la corde  \n");
			//Création de la corde 
				corde2 c;
				c.p1 = poly[i];
				c.p2 = poly[i + increment];
				
				/*if ( t == n - 2){
					c.p1 = poly[i];
					c.p2 = poly[0];
				} 
				if ( t == n - 1){
					c.p1 = poly[i];
					c.p2 = poly[1];
				} */

				x = i;	
				y = t - 1;

				c.lon = coutcorde2(c);
				NB_sommets = t - i +1 ;


			
			//printf("Recherche \n");
			// Coordonées x,y utilsées pour garder en mémoir la meilleur case du tableau

			int somme_corde_min = tab_sous_poly[x][y].somme_corde + c.lon;
			int somme_corde_2 = 0 ;


		
			//Attention quand 4 sommets on regarde que 2 cordes 
			/*if(NB_sommets == 4 ){
				somme_corde_2 = tab_sous_poly[i+1][t].somme_corde + c.lon;
				if ( somme_corde_2 < somme_corde_min){
					somme_corde_min = somme_corde_2;
					//ATTENTION on "inverse" x et y pour le tableau au lieu de regarder (1,2) on va regarder (2,1)
					x = i+1;
					y = t;
				}
			}*/
			printf("____________________________________________________________________________________\n");
			printf("nb sommets %d \n", NB_sommets);
			printf("j = %d \n", j);
			printf("i = %d \n", i);
			printf("t = %d \n", j+i);

			somme_corde_2 = tab_sous_poly[i+1][t].somme_corde + c.lon;
			printf("s1=%d     s2=%d  \n",somme_corde_min,somme_corde_2);
			if ( somme_corde_2 < somme_corde_min){
				somme_corde_min = somme_corde_2;
				x = i+1;
				y = t;
			}

			printf("x=%d     y=%d  \n", x,y);

			if(NB_sommets >= 5){
				for(k = 2 ; k <= NB_sommets - 3; k++){	
					somme_corde_2 = tab_sous_poly[i][i+k-2].somme_corde + tab_sous_poly[k][t].tab_corde[0].lon + c.lon;
					printf("somme corde=%d     somme corde 2=%d \n", somme_corde_min, somme_corde_2);
					if ( somme_corde_2 < somme_corde_min){
						somme_corde_min = somme_corde_2;
						printf("somme corde=%d     somme corde 2=%d \n", somme_corde_min, somme_corde_2);
						//Même remarque que au dessus pour le tableau et x,y
						printf("x=%d     y=%d  x1=%d y1=%d \n", x,y,x1,y1);
						x = i;
						y = i + k - 2;
						x1 = i+k;
						y1 = t;
						printf("x=%d     y=%d  x1=%d. y1=%d \n", x,y,x1,y1);
					}
				}
			}


			
//printf("Fin recherche \n");


			//printf("corde A AJOUTER", i);
			
			printf("Ajout de la corde  \n");
			//Enregistrement dans notre tableau de corde

			tab_sous_poly[i][t].somme_corde = somme_corde_min;
			tab_sous_poly[i][t].nb_corde = tab_sous_poly[x][y].nb_corde + 1; //le +1 est pour la nouvelle corde ajoutée


			//Cas ou on doit enregistrer deux tableaux de cordes et non pas un seul
			if (( x1 != -1 ) && ( y1 != -1 )){
				printf("Ajout de 2 cordes \n");
				tab_sous_poly[i][t].nb_corde +=1;
				suite = 1;
			}

			ArraySize = tab_sous_poly[i][t].nb_corde;

			tab_sous_poly[i][t].tab_corde = malloc(ArraySize*sizeof(corde2));

			if (tab_sous_poly[i][t].tab_corde == NULL) {
  				fprintf(stderr, "malloc failed\n");
			}


			printf("Cordes tot = %d \n",ArraySize);
			//Enregistrement de la corde c
			tab_sous_poly[i][t].tab_corde[0] = c  ;

			//Enregistrement du tableau de corde 
			for(l = 1; l < (ArraySize - suite); l++){
				tab_sous_poly[i][t].tab_corde[l] = tab_sous_poly[x][y].tab_corde[l-1] ;
			}
			
			if(suite==1){
 				tab_sous_poly[i][t].tab_corde[ArraySize - 1] = tab_sous_poly[x1][y1].tab_corde[0];
				x1 = -1;
				y1 = -1;
				suite = 0;
			}
			
			//printf("suite \n");
			
			print_piou(tab_sous_poly[i][t]);

			NB_sommets = save;

						
		}		
	}
	if ( tab_sous_poly[0][n-4].somme_corde < tab_sous_poly[1][n - 3].somme_corde){
		x = 0;
		y = n - 4;
	}
	else{

		x = 1;
		y = n - 3;
	}
	printf("Comparaisons solutions______________________________________________________________\n");
	print_piou(tab_sous_poly[0][n-4]);
	printf("____________________________________________________________________________________\n");
	print_piou(tab_sous_poly[1][n-3]);
	printf("____________________________________________________________________________________\n");
	
	
	printf("ENREGISTREMENT SOLUTION FINAL \n");
	printf("x=%d y=%d \n",x,y);
	//On enregistre la solution dans le tableau de solution
	for (i = 0; i < tab_sous_poly[x][y].nb_corde; i++){
		solution[i] = tab_sous_poly[x][y].tab_corde[i];
		//printf(" i = %d \n",i);
	}
	print_piou(tab_sous_poly[x][y]);

	printf("Fin  enregistrement\n");
	printf("____________________________________________________________________________________\n");
	
	/*for ( i = 0; i < n - 2; i++){
		for ( j = i; j < n - 2; j++){
			free(tab_sous_poly[i][j].tab_corde);
		} 
	}*/

}





