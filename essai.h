#include "genpoly.h"


int validecorde(int n,int i,int j,corde solution[]);

void recessai(point poly[],corde tabcorde[],int n,corde solution[],int i,corde finalsol[],float* meilleur);

corde * gencorde(int n,point poly[]);

void savesolution(int n,corde sol[],corde finalsol[]);

void solessai(int n,point poly[],corde solution[]);
