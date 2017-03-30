
#include <stdio.h>
#include <stdlib.h>
#include "essai.h"


int validecorde(int n,int i,int j,corde solution[]){
  int k;
  //verif (i-j) pas dans solution
  //verif coupe pas autre corde dans solution
  for(k=0;k<n-3;k++){//parcours des cordes dans solutions

    if((solution[k].p1==i && solution[k].p2==j)//identique a sol[k]
       ||
       (solution[k].p1<i && i<solution[k].p2 && (j<solution[k].p1 || solution[k].p2<j))//coupe
       ||
       (solution[k].p1<j && j<solution[k].p2 && (i<solution[k].p1 || solution[k].p2<i))//coupe
       ){
      return 0;
    }
  }
  return 1;
}



void solessai(int n,point poly[],corde solution[]){
  int k;
 

  //parcours récursif de tout les arc, choix de les prendre ou non, sauvegarde du meilleur résul
  corde soltemp[n-3];

  corde c;
  c.p1=-1;
  c.p2=-1;
  for(k=0;k<n-3;k++){
    soltemp[k]=c;
  }

  info_essai info;

  info.n=n;
  info.tabcorde=gencorde(n,poly);
  info.poly=poly;
  
  info.solution=soltemp;
  info.finalsol=solution;


  int compteur=0;
  float score=400.0*n;

  //printf("val score init %f\n",score);
  recessai(info,0,0,&score,&compteur);

  printf("compteur : %d\n",compteur);


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
void recessai(info_essai info,int i,int ki,float* meilleur,int*compteur){
  int k;
  int z;
  if(i==info.n-3){
    //printf("sol trouvé ! %f\n",coutsol(info.n,info.poly,info.solution));
    *compteur=*compteur+1;

    if(coutsol(info.n,info.poly,info.solution)<*meilleur ){//fin du parcours il faut save la solution
      savesolution(info.n,info.solution,info.finalsol);
      *meilleur=coutsol(info.n,info.poly,info.solution);
      //printf("acces a meilleur %f\n",*meilleur);
    }
  }else{// cas du choix pour remplir la case i de la sol
    //printf("val de i %d \n",i);
    for(k=ki;k<(info.n-3)*info.n/2;k++){//on parcours toute les corde restantes
      //printf("increment k=%d,i=%d\n",k,i);
      if(validecorde(info.n,info.tabcorde[k].p1,info.tabcorde[k].p2,info.solution)){//si la corde est choisissable
	//printf("corde valide : %d-%d\n",info.tabcorde[k].p1,info.tabcorde[k].p2);
	//printf("parmis :\n");
	/**
	for(z=0;z<info.n-3;z++){

	  printf("(%d-%d),",info.solution[z].p1,info.solution[z].p2);
	}
	printf("\n");
	**/

	info.solution[i]=info.tabcorde[k];//on la choisie

	recessai(info,i+1,k+1,meilleur,compteur);//on choisie les autres

	corde c;
	c.p1=-1;
	c.p2=-1;
	info.solution[i]=c;
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
