

#ifndef LISTE_SERPENT_H
#define LISTE_SERPENT_H


#include <stdlib.h>
#include <stdio.h>

#define ROUGE "\33[41m  \33[00m"
#define VERT "\33[42m  \33[00m"
#define JAUNE "\33[43m  \33[00m"
#define BLEU "\33[44m  \33[00m"
#define VIOLET "\33[45m  \33[00m"
#define CYAN "\33[46m  \33[00m"
#define BLANC "\33[47m  \33[00m"


#include "Serpent.h"
#include "Grille.h"




struct section {

    char * couleur;
    struct section * suivant;
    int longueur;

};



struct section * creer_section(int longueur);
void couleur_section (struct section **s);
void detruire_section(struct section **m);
char * couleur_aleatoire();



#endif