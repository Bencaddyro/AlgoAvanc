#include "genpoly.h"




typedef struct {
  int n;
  corde*tabcorde;
  point*poly;

  corde*solution;
  corde*finalsol;

} info_essai;


int validecorde(int n,int i,int j,corde solution[]);

void recessai(info_essai info,int i,int ki,float* meilleur,int*compteur);

corde * gencorde(int n,point poly[]);

void savesolution(int n,corde sol[],corde finalsol[]);

void solessai(int n,point poly[],corde solution[]);



