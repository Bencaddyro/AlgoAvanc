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
	int i,j,k,l,t,x,y, x1, y1;
	int ArraySize;
	int nbCordeAjout;	
	int NB_sommets =4; //Correspond au nombre de sommets du sous-polygone (au minimum 4)
	int nbCordesArray1, nbCordesArray2 = 0;
	int temp1, temp2, tempNb;
	int increment = 2;
	int somme_corde_min;
	int somme_corde_2 ;


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
		c.lon = coutcorde2(c);
		//1ère diagonale du tableau
		tab_sous_poly[i][i].somme_corde = c.lon;
		tab_sous_poly[i][i].nb_corde = 1; //On ne regarde qu'une seule corde à cette étape
		tab_sous_poly[i][i].tab_corde = malloc(1*sizeof(corde2));
		tab_sous_poly[i][i].tab_corde[0] = c ;
		//print_piou(tab_sous_poly[i][i]);
	}
	//printf("FIN INITIALISATION \n");
	
	//printf("DEBUT PARCOURS TABLEAU \n");

	for(j = 1; j < n-3; j++){	
		increment ++;
		for(i = 0; i < (n - j - 2); i++){
			t = j + i;
			NB_sommets = increment +  1 ; //Nombre de sommet du sous polygonne allant du sommet i au sommet i+increment 
			
			
			//Création de la corde 
			corde2 c;
			c.p1 = poly[i];
			c.p2 = poly[i + increment];
			c.lon = coutcorde2(c);
			
			
			// Coordonées x,y utilsées pour garder en mémoire la meilleur case du tableau 
			x = i;	
			y = t - 1;
			//On regarde la case associée à la corde allant de i à i+increment-1
			somme_corde_min = tab_sous_poly[x][y].somme_corde + c.lon;
			somme_corde_2 = 0 ;

			//printf("___________________________________________________________________________________\n");
			//printf("nb sommets %d \n", NB_sommets);
			//printf("i = %d \n", i);
			//printf("t = %d \n", j+i);

			//On regarde la case associée à la corde allant de i+1 à i+increment
			somme_corde_2 = tab_sous_poly[i+1][t].somme_corde + c.lon;
			//printf("s1=%d     s2=%d  \n",somme_corde_min,somme_corde_2);
			//On compare les deux longeures observées et on conserve la case du tableau donnant la longueur minimale
			if ( somme_corde_2 < somme_corde_min){
				somme_corde_min = somme_corde_2;
				x = i+1;
				y = t;
			}
			nbCordeAjout = tab_sous_poly[x][y].nb_corde;
			nbCordesArray1 = nbCordeAjout;
			//printf("x=%d     y=%d  \n", x,y);

			//On regarde les cases associées aux cordes allant de i à i+k et de i+k+1 à i+increment (k allant de 2 au nombre de sommets du sous polygone - 3)
			if(NB_sommets >= 5){
				for(k = 2 ; k <= NB_sommets - 3; k++){	
					if(k==2){
						somme_corde_2 = tab_sous_poly[i][i+k-2].tab_corde[0].lon  + tab_sous_poly[i+k][t].somme_corde + c.lon; 
						tempNb = tab_sous_poly[i+k][t].nb_corde + 1;
						temp1 = 1;
						temp2 = tab_sous_poly[i+k][t].nb_corde;
					}
					if((k>2) && (k==NB_sommets - 3)){
						somme_corde_2 = tab_sous_poly[i][i+k-2].somme_corde + tab_sous_poly[i+k][t].tab_corde[0].lon + c.lon; 
						tempNb = tab_sous_poly[i][i+k-2].nb_corde + 1;
						temp1 = tab_sous_poly[i][i+k-2].nb_corde;
						temp2 = 1;
					}
					if((k>2) && (k<NB_sommets - 3)){
						somme_corde_2 = tab_sous_poly[i][i+k-2].somme_corde + tab_sous_poly[i+k][t].somme_corde + c.lon;	
						tempNb = tab_sous_poly[i][i+k-2].nb_corde + tab_sous_poly[i+k][t].nb_corde;
						temp1 = tab_sous_poly[i][i+k-2].nb_corde ;
						temp2 = tab_sous_poly[i+k][t].nb_corde;
					}

					//printf("somme corde=%d     somme corde 2=%d \n", somme_corde_min, somme_corde_2);
					if ( somme_corde_2 < somme_corde_min){
						somme_corde_min = somme_corde_2;
						x = i;
						y = i + k - 2;
						x1 = i+k;
						y1 = t;
						nbCordeAjout = tempNb;
						nbCordesArray1 = temp1;
						nbCordesArray2 = temp2;
						//printf("x=%d     y=%d  x1=%d. y1=%d \n", x,y,x1,y1);
					}
				}
			}

			//printf("nbCordesArray1 = %d nbCordesArray2 = %d \n", nbCordesArray1, nbCordesArray2);
			
			//printf("Fin recherche \n");

			
			//printf("Ajout de la corde  \n");
			//Enregistrement dans notre tableau de corde

			tab_sous_poly[i][t].somme_corde = somme_corde_min;
			tab_sous_poly[i][t].nb_corde = nbCordeAjout + 1; //le +1 est pour la nouvelle corde ajoutée
			
			ArraySize = tab_sous_poly[i][t].nb_corde;
			tab_sous_poly[i][t].tab_corde = malloc(ArraySize*sizeof(corde2));

			if (tab_sous_poly[i][t].tab_corde == NULL) {
  				fprintf(stderr, "malloc failed\n");
			}
			
			//Enregistrement de la corde c
			tab_sous_poly[i][t].tab_corde[0] = c  ;

			//Enregistrement du/des tableau(x) de cordes  
			for(l = 0; l < nbCordesArray1 ; l++){
				tab_sous_poly[i][t].tab_corde[l+1] = tab_sous_poly[x][y].tab_corde[l] ;
			}
			
			if(nbCordesArray2 != 0){
 				for(l = 0; l < nbCordesArray2 ; l++){
					tab_sous_poly[i][t].tab_corde[l + nbCordesArray1 + 1] = tab_sous_poly[x1][y1].tab_corde[l] ;
				}
				nbCordesArray2 = 0;
			}
			
			//print_piou(tab_sous_poly[i][t]);
						
		}		
	}

	//On a fini de remplir notre tableau, nous allons maintenant choisir la meilleure solution, pour ce faire nous allons comparer les différentes solutions possibles
	if ( tab_sous_poly[0][n-4].somme_corde < tab_sous_poly[1][n - 3].somme_corde){
		x = 0;
		y = n - 4;
	}
	else{

		x = 1;
		y = n - 3;
	}
	somme_corde_min = tab_sous_poly[x][y].somme_corde;
	nbCordesArray1 = tab_sous_poly[x][y].nb_corde;

	if(n >= 5){
		for(k = 2 ; k <= n - 3; k++){	
			if(k==2){
				somme_corde_2 = tab_sous_poly[0][0].tab_corde[0].lon  + tab_sous_poly[2][n-3].somme_corde; 
				nbCordeAjout = tab_sous_poly[2][n-3].nb_corde + 1;
				temp1 = 1;
				temp2 = tab_sous_poly[2][n-3].nb_corde;
			}
			if(k==n - 3){
				somme_corde_2 = tab_sous_poly[0][n-5].somme_corde + tab_sous_poly[n-3][n-3].tab_corde[0].lon;  
				nbCordeAjout = tab_sous_poly[0][n-5].nb_corde + 1;
				temp1 = tab_sous_poly[0][n-5].nb_corde;
				temp2 = 1;
			}
			if((k>2) && (k < n - 3)){
				somme_corde_2 = tab_sous_poly[0][k-2].somme_corde + tab_sous_poly[k][n-3].somme_corde;	
				nbCordeAjout = tab_sous_poly[0][k-2].nb_corde + tab_sous_poly[k][n-3].nb_corde;
				temp1 = tab_sous_poly[0][k-2].nb_corde ;
				temp2 = tab_sous_poly[k][n-3].nb_corde;
			}
			//printf("somme corde=%d     somme corde 2=%d \n", somme_corde_min, somme_corde_2);
			if ( somme_corde_2 < somme_corde_min){
				somme_corde_min = somme_corde_2;
				x = 0;
				y = k - 2;
				x1 = k;
				y1 = n-3;
				nbCordesArray1 = temp1;
				nbCordesArray2 = temp2;
				//printf("x=%d     y=%d  x1=%d. y1=%d \n", x,y,x1,y1);
			}			
		}
	}
	
	//printf(" ENREGISTREMENT SOLUTION FINAL \n");
	//On enregistre la solution dans le tableau de solution
	//printf("nbCordesArray1 = %d nbCordesArray2 = %d \n", nbCordesArray1, nbCordesArray2);

	for (l = 0; l < nbCordesArray1 ; l++){
		solution[l] = tab_sous_poly[x][y].tab_corde[l] ;
	}
	if(nbCordesArray2 != 0){
 		for(l = 0; l < nbCordesArray2 ; l++){
			solution[l + nbCordesArray1] = tab_sous_poly[x1][y1].tab_corde[l] ;
		}
	}

	/*printf("Fin  enregistrement\n");
	
	printf("____________________________________________________________________________________\n");

	for (i = 0; i < n-3; i++){
		printf("corde %d \n", i);
		printf("point 1 : x = %d , y = %d , lon = %f \n", solution[i].p1.x, solution[i].p1.y, solution[i].lon);
		printf("point 2 : x = %d , y = %d , lon = %f \n", solution[i].p2.x, solution[i].p2.y, solution[i].lon);
	}
		printf("____________________________________________________________________________________\n");*/

}





