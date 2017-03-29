
typedef struct{
	int somme_corde; //Somme de toutes les cordes ajoutées 
	int nb_corde;	//Nombres totales de cordes dans le sous-polygone observé
	corde tab_corde[nb_corde];	//Tableau contenant toutes les cordes retenues
} piou;

void soldynamique(int n,point poly[],corde solution[]);
