#include "main.h"
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
  int n=atoi(argv[1]);
  point poly[n];
  corde solution[3]; //[n-3];
  corde2 solution2[3]; //[n-3];
  int ok=1;
  //point exemple[7];
  //point p;

  /*
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

  */


/*
  p.x=0;
  p.y=10;
  exemple[0]=p;
  p.x=0;
  p.y=20;
  exemple[1]=p;
  p.x=8;
  p.y=26;
  exemple[2]=p;
  p.x=15;
  p.y=26;
  exemple[3]=p;
  p.x=27;
  p.y=21;
  exemple[4]=p;
  p.x=22;
  p.y=12;
  exemple[5]=p;
  p.x=10;
  p.y=0;
  exemple[6]=p;
*/

  /*
  tracerpoly(7,exemple);
  solessai(n,exemple,solution);
  //solglouton(7,exemple,solution);
  printsol(7,exemple,solution);
  tracersol(7,exemple,solution);
  printf("valeur de la solution essai successif : %f\n",coutsol(n,exemple,solution));
  */

  /*
  SDL_Flip(affichage);
  attendreTouche();
  SDL_FillRect(affichage,NULL,Color(0,0,0));

  tracerpoly(7,exemple);
  //solessai(n,exemple,solution);
  solglouton(7,exemple,solution);
  printsol(7,exemple,solution);
  tracersol(7,exemple,solution);
  printf("valeur de la solution glouton : %f\n",coutsol(n,exemple,solution));
  */


  
  while(ok){
  genpoly(n,poly);

  tracerpoly(n,poly);
  //solglouton(n,poly,solution);
  soldynamique(n,poly,solution2);
	//soldynamique(6,exemple,solution2);
  tracersol2(n,poly,solution2);
 printf("valeur de la solution algo dynamique : %f\n",coutsol2(n,solution2));  

  //tracerpoly(n,poly);
  solessai(n,poly,solution);
  tracersol(n,poly,solution);
 printf("valeur de la solution essai successif : %f\n",coutsol(n,poly,solution));

  attendreTouche(&ok);

  SDL_FillRect(affichage,NULL,Color(0,0,0));
  SDL_Flip(affichage);
  }
  

  /*point *poly2;
  int n2;

  genpoly2(n,poly,&n2,&poly2);

  printf("%d\n",n2);
  tracerdebug(n,poly);

  attendreTouche(&ok);
  tracerpoly(n2,poly2);
*/
  attendreTouche(&ok);

  SDL_Quit();

  return EXIT_SUCCESS;
}
