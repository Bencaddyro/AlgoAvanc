#include <stdio.h>
#include "dynamique.h"
#include "genpoly.h"

void soldynamique(int n,point poly[],corde solution[]){
	int s_deb, s_fin;	//Représentes les sommets de débuts et de fin des sous-polygonnes étudié 
	int taille = n+2;	//Longeur du tableau tab_sous_poly	
	piou tab_sous_poly[n][taille];	//On ne remplira que le triangle suppérieur
	int i,j;

	//Initialisation de tab_sous_poly
	for(i = 0; i < n; i++){
		//Création de la corde
		corde2 c;
		c.p1 = poly[i];
		c.p2 = poly[i+2];
		c.lon = coutcorde2(c);
		//1ère diagonale du tableau
		tab_sous_poly[i][i+2].somme_corde = c.lon;
		tab_sous_poly[i][i+2].nb_corde = 1; //On ne regarde qu'une seule corde à cette étape
		tab_sous_poly[i][i+2].tab_corde[0] = c ;
		//Attention pour le tracer des 2 derniéres cordes (Sn-1,S0) et (Sn,S1) d'ou le if
		if(i <= taille-2){
			corde2 c;
			c.p1 = poly[i];
			c.p2 = poly[i-n-2]; //TODO: Vérifier l'équation!!!
			c.lon = coutcorde2(c);
			//1ère diagonale du tableau
			tab_sous_poly[i][i+2].somme_corde = c.lon;
			tab_sous_poly[i][i+2].nb_corde = 1; //On ne regarde qu'une seule corde à cette étape
			tab_sous_poly[i][i+2].tab_corde[0] = c ;
		}
	}

	//TODO : Remplissage du tableau (par diagonale)
	for(i = 3; i < n; i++){
		for(j = 0; j < n; j++){
			//Création de la corde TODO 
			corde2 c;
			c.p1 = poly[j];
			c.p2 = poly[i+j];
			c.lon = coutcorde2(c);
			//Remplissage de la diagonale TODO
			
		}		
	}
}



/*
typedef struct{
	int somme_corde; //Somme de toutes les cordes ajoutées 
	int nb_corde;	//Nombres totales de cordes dans le sous-polygone observé
	corde tab_corde[nb_corde];	//Tableau contenant toutes les cordes retenues
} piou;*/
