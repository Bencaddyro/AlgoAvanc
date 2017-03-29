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


int compa(const void * p1, const void * p2){
  //return ( *(point*)a - *(point*)b );

  return 0;

}



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


void genpoly2(int n,point poly[]){
  srand(time(NULL));
  point p;
  int i;
  for(i=0;i<n;i++){//génération point random
    p.x=rand()%400;
    p.y=rand()%400;
    poly[i]=p; 
  };

  //recherche min des abcisse & ordonné (a remonter dans la génération)

  //tri en fonction de l'angle(croissant)

  qsort(poly,n,sizeof(point),compa);

  for(i=0;i<n;i++){
    

    
  }







}


float coutcorde(point poly[],corde c){
  return sqrt((poly[c.p1].x-poly[c.p2].x)*(poly[c.p1].x-poly[c.p2].x)+(poly[c.p1].y-poly[c.p2].y)*(poly[c.p1].y-poly[c.p2].y));
}

float coutsol(int n,point poly[],corde solution[]){
  float res=0;
  int i;
  for(i=0;i<n-3;i++){
    res+=coutcorde(poly,solution[i]);
  }
  return res;
}
