#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "genpoly.h"
#include "graphique.h" 

int MaxDist=200;


int comp(const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}



//Génération de polygone___________________________________________________________________________________

void genpoly(int n,point poly[]){
  int i;
  int angle[n];
  int dist[n];
  srand(time(NULL));

 
  for(i=0;i<n;i++){
    angle[i]=rand()%360;//génération de n angle random
    
    dist[i]=150;//+rand()%10; //génération de n longueur (pas du tout) pseudo-random
  };

  //tri des tableau sous forme croissante
  qsort(angle,n,sizeof(int),comp);
  //qsort(dist,n,sizeof(int),comp);

  //remplissage tableau point

  for(i=0;i<n/2;i++){

    poly[i].x=dist[2*i]*cos(angle[i]*M_PI/180)+250;
    poly[i].y=dist[2*i]*sin(angle[i]*M_PI/180)+250;

    poly[n-i-1].x=dist[2*i+1]*cos(angle[n-i-1]*M_PI/180)+250;
    poly[n-i-1].y=dist[2*i+1]*sin(angle[n-i-1]*M_PI/180)+250;    

  };
  if(n%2){
    poly[n/2].x=(int)dist[n-1]*cos(angle[n/2]*2*M_PI/360)+250;
    poly[n/2].y=(int)dist[n-1]*sin(angle[n/2]*2*M_PI/360)+250;
  }
  
}


//____________________________________________________________________________________________________________

void genpoly2(int n,point poly[]){
  srand(time(NULL));
  point p;
  int i;
  int minx=500,miny=500,index;
  for(i=0;i<n;i++){//génération point random
    p.x=rand()%400+50;
    p.y=rand()%400+50;
    poly[i]=p;

    //recherche min des abcisse & ordonné (a remonter dans la génération)
    if(p.y<miny){
      minx=p.x;
      miny=p.y;
      index=i;
    }

  }


  //fonction de comparaison
  int compa(const void * p1, const void * p2){
    int xa=minx;
    int ya=miny;
    int xb=(*(point*)p1).x;
    int yb=(*(point*)p1).y;
    int xc=(*(point*)p2).x;
    int yc=(*(point*)p2).y;
    
    if(minx>=(*(point*)p1).x && minx>=(*(point*)p2).x){//les 2 a droite
      //theta p1 > theta p2 equivalent cos(p1)<cos(p2)
      float ab=sqrt((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb));
      float abb=abs(xa-xb);

      float ac=sqrt((xa-xc)*(xa-xc)+(ya-yc)*(ya-yc));
      float acc=abs(xa-xc);
      
      float cosb=abb/ab;
      float cosc=acc/ac;
      
      if(cosb<cosc){
	return 1;
      }else{
	return -1;
      }
    }
    if(minx>=(*(point*)p1).x && minx<=(*(point*)p2).x){//le premier a droite le 2eme a gauche
      //p1<p2
      return -1;
    }
    if(minx<=(*(point*)p1).x && minx>=(*(point*)p2).x){//le premier a gauche le 2eme a droite
      //p1>p2
      return 1;
    }
    if(minx<=(*(point*)p1).x && minx<=(*(point*)p2).x){//les 2 a gauche
      float ab=sqrt((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb));
      float abb=abs(xa-xb);

      float ac=sqrt((xa-xc)*(xa-xc)+(ya-yc)*(ya-yc));
      float acc=abs(xa-xc);
      
      float cosb=abb/ab;
      float cosc=acc/ac;
      
      if(cosb<cosc){
	return -1;
      }else{
	return 1;
      }
    }
    return 0;
  }

  point tmp=poly[0];
  poly[0]=poly[index];
  poly[index]=tmp;

  //tri en fonction de l'angle(croissant)

  printf("lolu : %d-%d\n",minx,miny);

  qsort(poly,n,sizeof(point),compa);

  //parcours avec ecart des mauvais point...

  int boool[n];
  int rejet=0;

  int x1=poly[0].x;
  int y1=poly[0].y;
  int x2=poly[1].x;
  int y2=poly[1].y;
  int x3=poly[2].x;
  int y3=poly[2].y;

  for(i=3;i<n;i++){
    if((x2-x1)*(y3-y1)-(y2-y1)*(x3-x1)>=0){
      //acceptation du point 2
      x1=x2;
      y1=y2;
      x2=x3;
      y2=y3;
      x3=poly[i].x;
      y3=poly[i].y;
    }else{
      //rejet du point 2
      boool[i]=1;
      rejet++;
      x2=x3;
      y2=y3;
      x3=poly[i].x;
      y3=poly[i].y;

    }
  }

  //recopie dans le poly de sortie
  int j=0;
  int * n2;
  point * poly2;


  *n2=n-rejet;
  poly2=malloc(sizeof(point)*(*n2));
  for(i=0;i<n;i++){
    if(boool[i]==0){
      poly2[j]=poly[1];
      j++;
    }
  }




}

//Calcul du cout d'une corde__________________________________________________________________________________

float coutcorde(point poly[],corde c){
  return sqrt((poly[c.p1].x-poly[c.p2].x)*(poly[c.p1].x-poly[c.p2].x)+(poly[c.p1].y-poly[c.p2].y)*(poly[c.p1].y-poly[c.p2].y));
}

float coutcorde2(corde2 c){
  return sqrt((c.p1.x-c.p2.x)*(c.p1.x-c.p2.x)+(c.p1.y-c.p2.y)*(c.p1.y-c.p2.y));
}
//________________________________________________________________________________________________________________

float coutsol(int n,point poly[],corde solution[]){
  float res=0;
  int i;
  for(i=0;i<n-3;i++){
    res+=coutcorde(poly,solution[i]);
  }
  return res;
}
