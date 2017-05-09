#include "main.h"
#include <time.h>
SDL_Surface*affichage;

void printsol(int n,point poly[],corde solution[]){
  int i;
  for(i=0;i<n-3;i++){
    printf(" arc: (%d,%d)-(%d,%d)\n",poly[solution[i].p1].x,poly[solution[i].p1].y,poly[solution[i].p2].x,poly[solution[i].p2].y);
  }
}

void tracerpoly(int n,point poly[]){
  int i;
  for(i=0;i<n-1;i++){
    drawLine(poly[i].x,poly[i].y,poly[i+1].x,poly[i+1].y,255,255,255);

    drawLine(poly[i].x+500,poly[i].y,poly[i+1].x+500,poly[i+1].y,255,255,255);
  }
  drawLine(poly[0].x,poly[0].y,poly[n-1].x,poly[n-1].y,255,255,255);
  drawLine(poly[0].x+500,poly[0].y,poly[n-1].x+500,poly[n-1].y,255,255,255);
  SDL_Flip(affichage);
}

void tracerdebug(int n,point poly[]){
  int i;
  int ok;
  for(i=0;i<n-1;i++){
    attendreTouche(&ok);
    SDL_Flip(affichage);
    drawLine(poly[i].x,poly[i].y,poly[i+1].x,poly[i+1].y,255,0,0);
    //printf("%d-%d\n",poly[i].x,poly[i].y);
  }
  //printf("%d-%d\n",poly[i].x,poly[i].y);
  attendreTouche(&ok);
}
	     
void printpoint(int n,point poly[]){ 
  int i;
  for(i=0;i<n;i++){
    printf("%d,%d\n",poly[i].x,poly[i].y);
  }
}


void tracersol(int n,point poly[],corde solution[]){
  int i;
  for(i=0;i<n-3;i++){
    SDL_Delay(300);
    //attendreTouche();
    drawLine(poly[solution[i].p1].x,poly[solution[i].p1].y,poly[solution[i].p2].x,poly[solution[i].p2].y,0,255,255);
    SDL_Flip(affichage);
  }
}

void tracersol2(int n,point poly[],corde2 solution[]){
  int i;
  for(i=0;i<n-3;i++){
    SDL_Delay(300);
    //attendreTouche();
    drawLine(solution[i].p1.x+500,solution[i].p1.y,solution[i].p2.x+500,solution[i].p2.y,0,255,255);
    SDL_Flip(affichage);
  }
}


int main(int argc, char** argv){
  initSDL();
  srand(time(NULL));

  int n=atoi(argv[1]);
  point poly[n];
  corde solution[n-3]; //[n-3];
  corde2 solution2[n-3]; //[n-3];
  int ok=1;  



  while(ok){
    genpoly(n,poly);

    tracerpoly(n,poly);



    solglouton(n,poly,solution);




    printf("valeur de la solution algo glouton : %f\n",coutsol(n,poly,solution));

    tracersol(n,poly,solution);


    soldynamique(n,poly,solution2);


    tracersol2(n,poly,solution2);
    printf("valeur de la solution algo dynamique : %f\n",coutsol2(n,solution2));  


    solessai(n,poly,solution);

    printf("valeur de la solution essai successif : %f\n",coutsol(n,poly,solution));
    printf("__________________________________________\n");
    attendreTouche(&ok);

    SDL_FillRect(affichage,NULL,Color(0,0,0));
    SDL_Flip(affichage);
  }
  
  SDL_Quit();

  return EXIT_SUCCESS;
}
