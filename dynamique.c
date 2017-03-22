#include <stdio.h>

void soldynamique(int n,point poly[],corde solution[]){
	var ent i,t,p;
	int vect[n][n];	//Tableau dans lequel on ne remplira que le triangle sup et contenant les valeurs de Ti,t
	point souspoly[];	//souspolygone observé
	for (i = 0, i < n, i++){
		for(t = 0, t < n, t++){
			vect[i][t] = 0;
		}
	}


	for (t = 4, t < n, t++){
		for (i = 0, i < n, i++){
			for(p = i, p < t, p++){	
			//On utilise des sous poligones pour remplire le tableau
			// pour ce faire on utilise le tableau souspoly contenant uniquement les point du sous polygone définie
				souspoly[p].x=poly[p].x;
				souspoly[p].y=poly[p].y;
				
				//Calcul du min dans le sous polygone$
				
			}
		}	
	}
}
