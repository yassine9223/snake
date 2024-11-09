#ifndef _SERPENT_H
#define _SERPENT_H
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>

#include "Grille.h"
#include "Liste_Section.h"
#include "Liste_Mouvement.h"
#include "Matrice.h"


struct serpent{
    struct tete * tete_serpent;
    struct section *premiere_sec;
    struct section *derniere_sec;
    struct liste_mouvement *move;
    int longueur_serpent;
};

struct tete {
    struct coordonnees pos ;
    char * couleur;
    struct section *premiere_section;
};

struct tete * creer_tete(int x, int y );
struct serpent * creer_serpent();
int est_vide_serpent(const struct serpent *l);
void ajouter_section_debut_serpent( struct serpent *l, struct section *m);
void ajouter_section_fin_serpent (struct serpent *l,struct section *m);
struct section * extraire_section_debut_serpent(struct serpent *l);
void desallouer_tete(struct serpent **l);
void desallouer_serpent(struct serpent **l);  
void afficher_tete_serpent( struct grille *p, struct serpent *s);
void grille_remplir2(struct grille *p, struct serpent *s,struct matrice *m);




#endif