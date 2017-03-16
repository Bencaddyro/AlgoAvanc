
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "graphique.h"


extern SDL_Surface* affichage;


Uint32 Color(int R, int G, int B)
{//Convertit RGB en long
	return 65536*R + 256*G + B;
}
 
void PutPixel(SDL_Surface*ecran ,int x, int y, Uint32 pixel)
{
    unsigned char * p;
    int bpp = ecran->format->BytesPerPixel;
    p = (unsigned char *)ecran->pixels + y * ecran->pitch + x * bpp;
    *(Uint32*)p = pixel;
}
 
void drawLine(int x1,int y1, int x2,int y2, int R, int G, int B)  // Bresenham
{
	unsigned long couleur = Color(R, G, B);
	int x,y;
	int Dx,Dy;
	int xincr,yincr;
	int erreur;
	int i;
 
	Dx = abs(x2-x1);
	Dy = abs(y2-y1);
	if(x1<x2)
		xincr = 1;
	else
		xincr = -1;
	if(y1<y2)
		yincr = 1;
	else			
		yincr = -1;
 
	x = x1;
	y = y1;
	if(Dx>Dy)
	{
		erreur = Dx/2;
		for(i=0;i<Dx;i++)
		{
			x += xincr;
			erreur += Dy;
			if(erreur>Dx)
			{
				erreur -= Dx;
				y += yincr;
			}
			PutPixel(affichage,x, y,couleur);
		}
	}
	else
	{
		erreur = Dy/2;
		for(i=0;i<Dy;i++)
		{
			y += yincr;
			erreur += Dx;
 
			if(erreur>Dy)
			{
				erreur -= Dy;
				x += xincr;
			}
			PutPixel(affichage,x, y,couleur);
		}
	}
}


void initSDL(void)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Erreur à l'initialisation de la SDL : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
 
  atexit(SDL_Quit);
  affichage = SDL_SetVideoMode(500, 500, 32, SDL_HWSURFACE);
 
  if (affichage == NULL) {
    fprintf(stderr, "Impossible d'activer le mode graphique : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
 
  SDL_WM_SetCaption("Projet Algo Avancé #Pangolin", NULL);
}


void attendreTouche(void)
{
  SDL_Event event;
 
  do
    SDL_WaitEvent(&event);
  while (event.type != SDL_QUIT && event.type != SDL_KEYDOWN);
}
