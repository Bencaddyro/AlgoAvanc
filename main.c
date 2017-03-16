#include "main.h"
SDL_Surface*affichage;

void printsol(int n,corde solution[]){
  int i;
  for(i=0;i<n-3;i++){
    printf(" arc: (%d,%d)-(%d,%d)\n",solution[i].p1.x,solution[i].p1.y,solution[i].p2.x,solution[i].p2.y);
  }
}

void tracerpoly(int n,point poly[]){
  int i;
  for(i=0;i<n-1;i++){
    drawLine(poly[i].x,poly[i].y,poly[i+1].x,poly[i+1].y,255,255,255);
  }
  drawLine(poly[0].x,poly[0].y,poly[n-1].x,poly[n-1].y,255,255,255);
}

void printpoint(int n,point poly[]){ 
  int i;
  for(i=0;i<n;i++){
    printf("%d,%d\n",poly[i].x,poly[i].y);
  }
}


void tracersol(int n,corde solution[]){
  int i;
  for(i=0;i<n-3;i++){
    SDL_Flip(affichage);
    attendreTouche();
    drawLine(solution[i].p1.x,solution[i].p1.y,solution[i].p2.x,solution[i].p2.y,0,255,255);

  }
}


int main(int argc, char** argv){
  initSDL();
  int n=atoi(argv[1]);
  point poly[n];
  genpoly(n,poly);
  corde solution[n-3];

  point exemple[7];
  point p;
  p.x=399;
  p.y=265;
  exemple[0]=p;
  p.x=389;
  p.y=306;
  exemple[1]=p;
  p.x=234;
  p.y=399;
  exemple[2]=p;
  p.x=181;
  p.y=383;
  exemple[3]=p;
  p.x=105;
  p.y=288;
  exemple[4]=p;
  p.x=104;
  p.y=213;
  exemple[5]=p;
  p.x=181;
  p.y=116;
  exemple[6]=p;
  /*
  tracerpoly(7,exemple);
  solglouton(7,exemple,solution);
  printsol(7,solution);
  tracersol(7,solution);
  */

  tracerpoly(n,poly);
  solglouton(n,poly,solution);
  printsol(n,solution);
  tracersol(n,solution);



  SDL_Flip(affichage);
  attendreTouche();
  SDL_Quit();

  return EXIT_SUCCESS;
}
