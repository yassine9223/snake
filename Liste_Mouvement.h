#ifndef LISTE_MOUVEMENT_H
#define LISTE_MOUVEMENT_H

#include "Grille.h"

enum direction{
    haut,
    bas,
    gauche,
    droite,
};



struct mouvement{
    int x;
    int y;
    enum direction mv;
    struct mouvement *next;
};

struct liste_mouvement{
    struct mouvement *premier;
    struct mouvement *dernier;
    int longueur;
};

struct mouvement * creer_mouvement();
struct liste_mouvement * creer_liste();
struct serpent * creer_serpent();
int est_vide_mouvement(const struct liste_mouvement *l);
void ajouter_mouvement_debut_liste( struct liste_mouvement *l, struct mouvement *m);
void ajouter_mouvement_fin_liste (struct liste_mouvement *l, struct mouvement *m);
struct mouvement * extraire_mouvement_debut_liste(struct liste_mouvement *l);
void desallouer_mouvement(struct mouvement **m);
void desallouer_liste(struct liste_mouvement **l);  
void mouvement_serpent(struct serpent *s, enum direction dern);

#endif