
#ifndef _Genpoly
#define _Genpoly

typedef struct{
  int x;
  int y;
} point;

typedef struct{
  int p1;
  int p2;
} corde;



void genpoly(int n,point poly[]);

float coutcorde(point poly[],corde c);

float coutsol(int n,point poly[],corde solution[]);

#endif
