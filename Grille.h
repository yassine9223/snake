

#ifndef _GRILLE_H
#define _GRILLE_H
#define MAX 20

#include <stdlib.h>
#include <stdio.h>







  struct coordonnees{
    unsigned int x;
    unsigned int y;
};


 struct grille {
    unsigned int m;
    unsigned int n;
    char ***tab;
    struct coordonnees fruit;

};



struct grille* grille_allouer(int lon,int lar);
void grille_vider(struct grille *p);
void grille_tirage_fruit(struct grille *f);
void grille_remplir(struct grille *p);
void grille_desallouer(struct grille **p);
void afficher(struct grille *p);
void grille_redessiner(struct grille * g);



#endif