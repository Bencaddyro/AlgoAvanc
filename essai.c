
#include <stdio.h>
#include <stdlib.h>
#include "essai.h"







void solessai(int n,point poly[],corde solution[]){

  //génération de tout les arc

  //parcours récursif de tout les arc, choix de les prednre ou non, sauvegarde du meilleur résul
  




}



//var global : tableau des arc
//score du "meilleur"
//vecteur solution courant
//structure pour save meilleur structure
void recessai(){





}



corde* gencorde(int n,point poly[]){
  int i,j,k=0;
  int nb=(n-3)*n/2;
  corde*tab=malloc(sizeof(corde)*nb);

  for(i=0;i<n-2;i++){

    for(j=i+2;j<n;j++){

      corde c;
      c.p1=i;
      c.p2=j;
      c.lon=coutcorde(poly,c);
      if(i!=0 || j!=n-1){
	tab[k]=c;
	k++;
	printf("nouvelcorde : %d-%d %f \n",c.p1,c.p2,c.lon);
      }
    }
  }

  
  return tab;
}
