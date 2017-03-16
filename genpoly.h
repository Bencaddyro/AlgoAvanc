
#ifndef _Genpoly
#define _Genpoly

typedef struct{
  int x;
  int y;
} point;

typedef struct{
  point p1;
  point p2;
} corde;



void genpoly(int n,point poly[]);

float coutcorde(corde c);

float coutsol(int n,corde solution[]);

#endif
