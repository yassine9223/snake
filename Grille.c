#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>

#include "Grille.h"
#include "Serpent.h"
#include "Liste_Section.h"

// Alloue dynamiquement une grille de dimensions lon x lar
struct grille * grille_allouer(int lon, int lar) {
    struct grille *result = malloc(sizeof(struct grille));
    if(result == NULL) {
        perror("Erreur d'allocation de la grille\n");
        exit(EXIT_FAILURE);
    }

    result->m = lon; 
    result->n = lar;

    // Alloue dynamiquement de l'espace pour le tableau de la grille
    result->tab = malloc(lon * sizeof(char **));
    if(result->tab == NULL) {
        perror("Erreur d'allocation pour le tableau\n");
        exit(EXIT_FAILURE);
    }

    int i, j;
    for(i = 0; i < lon; ++i) {
        // Alloue dynamiquement de l'espace pour chaque ligne du tableau
        result->tab[i] = malloc(lar * sizeof(char *));
        if(result->tab[i] == NULL) {
            perror("Erreur d'allocation pour le tableau 2\n");
            exit(EXIT_FAILURE);
        }

        for (j = 0; j < lar; ++j) {
            // Alloue dynamiquement de l'espace pour chaque case du tableau
            result->tab[i][j] = malloc(8 * sizeof(char));
            if(result->tab[i][j] == NULL) {
                perror("Erreur d'allocation pour le tableau 3\n");
                exit(EXIT_FAILURE);
            } 
        }
    }

    return result;
}

// Vide la grille en remplissant chaque case avec des espaces
void grille_vider(struct grille *p) {
    int i, j;

    for(i = 0; i < p->m; ++i) {
        for(j = 0; j < p->n; ++j) {
             strcpy(p->tab[i][j], "\33[40m  \33[00m"); // Copie deux espaces dans chaque case
        }
    }
}

// Tire aléatoirement les coordonnées du fruit dans la grille
void grille_tirage_fruit(struct grille *f) {
    f->fruit.x = rand() % f->m; // Tire les coordonnées x du fruit 
    f->fruit.y = rand() % f->n; // Tire les coordonnées y du fruit 
}

// Remplit la case du fruit dans la grille avec une couleur spécifique
void grille_remplir(struct grille *p) {
    strcpy(p->tab[p->fruit.x][p->fruit.y],"\33[41m  \33[00m");
}

// Désalloue la mémoire occupée par la grille
void grille_desallouer(struct grille **p) {
    if(*p != NULL) {
        int i, j;

        // Parcours chaque case de la grille pour libérer la mémoire allouée
        for(i = 0; i < (*p)->m; ++i) {
            for(j = 0; j < (*p)->n; ++j) {
                free((*p)->tab[i][j]);
            }
            free((*p)->tab[i]);
        }
        free((*p)->tab);
        free(*p);
        *p = NULL;
    }
}

// Redessine la grille avec les contours
void grille_redessiner(struct grille *p) {
    printf("\033[2J\033[H"); // Efface l'écran et place le curseur en haut à gauche
    int i, j;

    printf("\033[47m"); // Définit la couleur de fond en blanc

    // Affichage du coin supérieur
    for(j = 0; j < p->n + 2; ++j)
        printf("  ");
    printf("\033[0m \33[1E"); // Réinitialise la couleur et déplace le curseur d'une ligne vers le bas

    // Affichage des lignes de la grille
    for(i = 0; i < p->m; ++i) {
        printf("\033[47m  \033[0m"); // Affiche le contour gauche
        for(j = 0; j < p->n; ++j)
            printf("%s", p->tab[i][j]); // Affiche chaque case de la grille
        printf("\033[47m  \033[0m\33[1E"); // Affiche le contour droit et déplace le curseur d'une ligne vers le bas
    }

    // Affichage du contour inférieur
    printf("\033[47m");
    for(j = 0; j < p->n + 2; ++j)
        printf("  ");
    printf("\033[0m\33[1E"); // Réinitialise la couleur et déplace le curseur d'une ligne vers le bas
}
