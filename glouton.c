#include <stdio.h>
#include "glouton.h"

void solglouton(int n,point poly[],corde solution[]){
  int vect[n];
  int i,indice,k;
  float min;
  float cout;
  for(i=0;i<n;i++){
    vect[i]=1;
  }

  for(k=0;k<n-3;k++){//trouve le kième arc solution
    min=500;
    for(i=0;i<n;i++){//on parcours les arc encore possible
      if(vect[i]){
	corde c;
	int pred=(i-1+n)%n;
	int suiv=(i+1)%n;

	while(!(vect[pred])){
	  pred=(pred-1+n)%n;
	}
	while(!(vect[suiv])){
	  suiv=(suiv+1)%n;
	}
	c.p1=pred;
	c.p2=suiv;
       	cout=coutcorde(poly,c);	
	if(cout<min){
	  min=cout;
	  solution[k]=c;
	  indice=i;
	}
      }
    }
    vect[indice]=0;
  }
}
