#ifndef _MATRICE_H
#define _MATRICE_H


#include <stdio.h>
#include <stdlib.h>


enum element{
    rien,
    fruit,
    serp,
    
};

struct matrice{
    int m;
    int n;
    enum element **tab;
};


struct matrice *creer_matrice(int m, int n);
void desallouer_matrice(struct matrice **m);
void matrice_vider(struct matrice *m);
//int manger_fruit(struct grille *p, struct serpent *s, struct matrice *m);
#endif