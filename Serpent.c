#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>

#include "Grille.h"
#include "Serpent.h"
#include "Liste_Section.h"
#include "Liste_Mouvement.h"
#include "Matrice.h"

// Crée une nouvelle tête de serpent avec les coordonnées spécifiées
struct tete * creer_tete(int x, int y) {
    srand(time(NULL));
    struct tete *nv = malloc(sizeof(struct tete));
    nv->pos.x = x;
    nv->pos.y = y;
    nv->couleur = malloc(8 * sizeof(char));
    nv->premiere_section = NULL;
    return nv;
}

// Crée un nouveau serpent vide
struct serpent * creer_serpent() {
    struct serpent *nv_serpent = malloc(sizeof(struct serpent));
    nv_serpent->premiere_sec = NULL;
    nv_serpent->derniere_sec = NULL;
    nv_serpent->longueur_serpent = 0;
    nv_serpent->move = creer_liste();
    return nv_serpent;
}

// Vérifie si le serpent est vide
int est_vide_serpent(const struct serpent *l) {
    return (l->premiere_sec == NULL);
}

// Ajoute une nouvelle section à la fin du serpent
void ajouter_section_fin_serpent(struct serpent *l, struct section *m) {
    m->suivant = NULL;
    if (est_vide_serpent(l) == 1) {
        l->premiere_sec = m;
    } else {
        l->derniere_sec->suivant = m;
    }
    l->derniere_sec = m;
    ++l->longueur_serpent;
}

// Extrait et retourne la première section du serpent
struct section * extraire_section_debut_serpent(struct serpent *l) {
    struct section *m = l->premiere_sec;
    if (m != NULL) {
        l->premiere_sec = m->suivant;
        --l->longueur_serpent;
        if (est_vide_serpent(l)) {
            l->derniere_sec = NULL;
        }
        m->suivant = NULL;
        if (m == NULL) {
            perror("Le serpent est vide\n");
            exit(EXIT_FAILURE);
        }
    }
    return m;
}

// Libère la mémoire allouée pour la tête du serpent
void desallouer_tete(struct serpent **l) {
    if (*l != NULL) {
        free((*l)->tete_serpent);
        (*l)->tete_serpent = NULL;
    }
}

// Désalloue la mémoire occupée par le serpent
void desallouer_serpent(struct serpent **l) {
    if (*l != NULL) {
        desallouer_tete(l);
        if ((*l)->premiere_sec != NULL) {
            while ((!est_vide_serpent(*l)) != 1) {
                struct section *m = extraire_section_debut_serpent(*l);
                detruire_section(&m);
            }
            free(*l);
            *l = NULL;
        }
    }
}

// Affiche la tête du serpent sur la grille
void afficher_tete_serpent(struct grille *p, struct serpent *s) {
    strcpy(p->tab[s->tete_serpent->pos.x][s->tete_serpent->pos.y], s->tete_serpent->couleur);
}

// Remplit la grille avec les informations du serpent et du fruit
void grille_remplir2(struct grille *p, struct serpent *s, struct matrice *m) {
    grille_vider(p);
    matrice_vider(m);

    // Place le fruit sur la grille et dans la matrice
    strcpy(p->tab[p->fruit.x][p->fruit.y], "\33[41m  \33[00m");
    m->tab[p->fruit.x][p->fruit.y] = fruit;
    
    // Place la tête du serpent sur la grille et dans la matrice
    int x = s->tete_serpent->pos.x;
    int y = s->tete_serpent->pos.y;
    strcpy(p->tab[x][y], s->tete_serpent->couleur);
    m->tab[x][y] = serp;

    // Place les sections du serpent sur la grille et dans la matrice
    struct section *current = s->premiere_sec;
    struct mouvement *m2 = creer_mouvement();
    m2 = s->move->premier;

    for (int i = 0; i < s->longueur_serpent; i++) {
        strcpy(p->tab[m2->x][m2->y], current->couleur);
        m->tab[m2->x][m2->y] = serp;
        current = current->suivant;
        m2 = m2->next;
    }

    // Redessine la grille avec les nouvelles informations
    grille_redessiner(p);
}
