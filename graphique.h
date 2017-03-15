
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>



unsigned long Color(int R, int G, int B);
void PutPixel(int x, int y, unsigned long pixel);
void drawLine(int x1,int y1, int x2,int y2, int R, int G, int B);

void initSDL(void);
void attendreTouche(void);
