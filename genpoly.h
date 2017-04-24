
#ifndef _Genpoly
#define _Genpoly

typedef struct{
  int x;
  int y;
} point;


typedef struct{
  int p1;
  int p2;
  float lon;
} corde;

typedef struct{
  point p1;
  point p2;
  float lon;
} corde2;


void genpoly(int n,point poly[]);
void genpoly2(int n,point poly[], int * n2,point* poly2[]);

float coutcorde(point poly[],corde c);
float coutcorde2(corde2 c);

float coutsol(int n,point poly[],corde solution[]);
float coutsol2(int n,corde2 solution[]);

#endif
