#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "graphique.h" 
#include "genpoly.h"

int main(int argc, char** argv){
  int i;
  initSDL();
  int n=atoi(argv[1]);
  point poly[n];
  genpoly(n,poly);
  
  for(i=0;i<n-1;i++){
    //PutPixel(poly[i].x,poly[i].y,Color(255,255,255));
    drawLine(poly[i].x,poly[i].y,poly[i+1].x,poly[i+1].y,255,255,255);
  }
  PutPixel(250,250,Color(255,255,255));

  //  drawLine(0,0,,200,255,255,255);


  attendreTouche();
  SDL_Quit();

  return EXIT_SUCCESS;
}
