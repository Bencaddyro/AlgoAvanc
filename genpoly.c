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



float coutcorde(corde c){
  return sqrt((c.p1.x-c.p2.x)*(c.p1.x-c.p2.x)+(c.p1.y-c.p2.y)*(c.p1.y-c.p2.y));
}

float coutsol(int n,corde solution[]){
  float res=0;
  int i;
  for(i=0;i<n;i++){
    res+=coutcorde(solution[i]);
  }
  return res;
}
