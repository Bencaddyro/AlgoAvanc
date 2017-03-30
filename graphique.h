
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>



Uint32 Color(int R, int G, int B);
void PutPixel(SDL_Surface*ecran,int x, int y, Uint32 pixel);
void drawLine(int x1,int y1, int x2,int y2, int R, int G, int B);

void initSDL(void);
void attendreTouche(int*bool);
