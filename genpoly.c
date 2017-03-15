#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "genpoly.h"


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
    //génération de n angle random
    angle[i]=rand()%360;
    //génération de n longueur random
    dist[i]=rand()%MaxDist;
  };

  //tri des tableau sous forme croissante
  qsort(angle,n,sizeof(int),comp);
  qsort(dist,n,sizeof(int),comp);

  //remplissage tableau point

  for(i=0;i<n/2;i++){
    /*
    poly[i].x=dist[2*i]*cos(angle[i]*2*M_PI/360)+250;
    poly[i].y=dist[2*i]*sin(angle[i]*2*M_PI/360)+250;

    poly[n-i-1].x=dist[2*i+1]*cos(angle[n-i-1]*2*M_PI/360)+250;
    poly[n-i-1].y=dist[2*i+1]*sin(angle[n-i-1]*2*M_PI/360)+250;
    */
    //utiliser la technique de la coquille saint jacques !
    

    poly[i].x=dist[2*i]*cos(i*M_PI/n)+250;
    poly[i].y=dist[2*i]*sin(i*M_PI/n)+250;

    poly[n-i-1].x=dist[2*i+1]*cos((2*i+1)*M_PI/(2*n))+250;
    poly[n-i-1].y=dist[2*i+1]*sin((2*i+1)*M_PI/(2*n))+250;


  };
  if(n%2){
    poly[n/2].x=(int)dist[n]*cos(angle[n/2]*2*M_PI/360)+250;
    poly[n/2].y=(int)dist[n]*sin(angle[n/2]*2*M_PI/360)+250;
  }
  
}


