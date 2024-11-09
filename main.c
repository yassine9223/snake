#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include "Grille.h"
#include "Liste_Section.h"
#include "Serpent.h"
#include "Fonctions_Jeu.h"
#include "Liste_Mouvement.h"

int main(int argc, char **argv){

    if(argc != 5){
        printf("Nombre d'argument incorrecte\n");
        exit(1);
    }
    int longueur = atoi(argv[1]);
    int largeur = atoi(argv[2]);
    int delai = atoi (argv[3]);
    int nb_joueur = atoi (argv[4]);
    


    struct grille *test= grille_allouer(longueur,largeur);
    struct matrice *m = creer_matrice(longueur,largeur);
    struct tete *head = creer_tete(2,1);
    
    
    
    //Affiche le motif de la tete du serpent
    strcpy(head->couleur,"\33[42m:)\33[00m");
    

    struct serpent *snake = creer_serpent();
    snake->tete_serpent = head;
    
    
    bouger_serpent(test,snake,m,delai,nb_joueur);
    
    
    return 0;
}