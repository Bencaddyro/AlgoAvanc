
#include <stdio.h>
#include <stdlib.h>
#include "essai.h"


int validecorde(int n,int i,int j,corde solution[]){
  int k;
  //verif (i-j) pas dans solution
  //verif coupe pas autre corde dans solution
  for(k=0;k<n-3;k++){//parcours des cordes dans solutions

    if((solution[k].p1==i && solution[k].p2==j)//différent de sol[k]
       ||
       (solution[k].p2==i && solution[k].p1==j)//différent de sol[k]
       ||
       (solution[k].p1<i && i<solution[k].p2 && (j<solution[k].p1 || solution[k].p2<j))//ne coupe pas
       ||
       (solution[k].p1<j && j<solution[k].p2 && (i<solution[k].p1 || solution[k].p2<i))//ne coupe pas
       ){
      return 0;
    }
  }
  return 1;
}



void solessai(int n,point poly[],corde solution[]){
  int k;
  //génération de tout les arc

  corde * tabcorde=gencorde(n,poly);

  //parcours récursif de tout les arc, choix de les prendre ou non, sauvegarde du meilleur résul
  corde soltemp[n-3];

  corde c;
  c.p1=-1;
  c.p2=-1;
  

  for(k=0;k<n-3;k++){
    soltemp[k]=c;
  } 

  float score=400.0*n;

  printf("val score init %f\n",score);
  recessai(poly,tabcorde,n,soltemp,0,solution,&score);



}

void savesolution(int n,corde sol[],corde finalsol[]){
  int i;
  for(i=0;i<n-3;i++){
    finalsol[i]=sol[i];
  }
}


//var global : tableau des corde
//score du "meilleur"
//vecteur solution courant (valeur non significative : NULL)
//structure pour save meilleur structure
//i itération sur la longueur de solution
//j itération sur la valeur dans tabcorde
void recessai(point poly[],corde tabcorde[],int n,corde solution[],int i,corde finalsol[],float* meilleur){
  int k;
  if(i==n-3){
    printf("sol trouvé ! %f\n",coutsol(n,poly,solution));
    if(coutsol(n,poly,solution)<*meilleur ){//fin du parcours il faut save la solution
      savesolution(n,solution,finalsol);
      *meilleur=coutsol(n,poly,solution);
      printf("acces a meilleur %f\n",*meilleur);
    }
  }else{// cas du choix pour remplir la case i de la sol
    //printf("val de i %d \n",i);
    for(k=0;k<(n-3)*n/2;k++){//on parcours toute les corde possibles
      printf("increment k=%d,i=%d\n",k,i);
      if(validecorde(n,tabcorde[k].p1,tabcorde[k].p2,solution)){//si la corde est choisissable
	printf("corde valide\n");
	solution[i]=tabcorde[k];//on la choisie

	recessai(poly,tabcorde,n,solution,i+1,finalsol,meilleur);//on choisie les autres

	corde c;
	c.p1=-1;
	c.p2=-1;
	solution[i]=c;
      }
    }
  }
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
	//	printf("nouvelcorde : %d-%d %f \n",c.p1,c.p2,c.lon);
      }
    }
  }

  
  return tab;
}
