#include <stdio.h>
#include <stdlib.h>

#include "Liste_Mouvement.h"
#include "Serpent.h"

// Crée un nouveau mouvement
struct mouvement * creer_mouvement() {
    struct mouvement * nv = malloc(sizeof(struct mouvement));
    nv->next = NULL;
    return nv;
}

// Crée une nouvelle liste de mouvements vide
struct liste_mouvement * creer_liste() {
    struct liste_mouvement * l = malloc(sizeof(struct liste_mouvement));
    l->premier = NULL;
    l->dernier = NULL;
    l->longueur = 0;
    return l;
}

// Vérifie si la liste de mouvements est vide
int est_vide_mouvement(const struct liste_mouvement *l) {
    return (l->premier == NULL);
}

// Ajoute un mouvement au début de la liste
void ajouter_mouvement_debut_liste(struct liste_mouvement *l, struct mouvement *m) {
    // Si la liste est vide, le nouveau mouvement est également le dernier
    if (est_vide_mouvement(l) == 1) {
        l->dernier = m; 
    }
    // Le mouvement devient le premier de la liste
    m->next = l->premier;
    l->premier = m;
    l->longueur++;
}

// Ajoute un mouvement à la fin de la liste
void ajouter_mouvement_fin_liste(struct liste_mouvement *l, struct mouvement *m) {
    // Le prochain mouvement du dernier devient le nouveau mouvement
    m->next = NULL;
    if (est_vide_mouvement(l) == 1) {
        l->premier = m;
    }
    l->dernier->next = m;
    // Le dernier élément de la liste devient le nouveau mouvement
    l->dernier = m;
    l->longueur++;
}

// Extrait et retourne le premier mouvement de la liste
struct mouvement * extraire_mouvement_debut_liste(struct liste_mouvement *l) {
    struct mouvement *m = l->premier;
    if (m != NULL) {
        // Le premier élément devient le suivant du mouvement extrait
        l->premier = m->next;
        l->longueur--;
        // Si la liste est vide, le dernier élément devient NULL
        if (est_vide_mouvement(l)) {
            l->dernier = NULL;
        }
        m->next = NULL;
        if (m == NULL) {
            perror("La liste est vide\n");
            exit(EXIT_FAILURE);
        }
    }
    return m;
}

// Libère la mémoire allouée pour un mouvement
void desallouer_mouvement(struct mouvement **m) {
    if ((*m) != NULL) {
        free(*m);
        *m = NULL;
    }
}

// Libère la mémoire allouée pour une liste de mouvements
void desallouer_liste(struct liste_mouvement **l) {
    if (*l != NULL) {
        // Tant que la liste n'est pas vide, extrait et libère chaque mouvement
        while (!est_vide_mouvement(*l)) {
            struct mouvement *m = extraire_mouvement_debut_liste(*l);
            desallouer_mouvement(&m);
        }
        // Libère la mémoire allouée pour la liste
        free(*l);
        *l = NULL;
    }
}

// Ajoute un mouvement au serpent
void mouvement_serpent(struct serpent *s, enum direction dern) {
    // Crée un nouveau mouvement
    struct mouvement *res = creer_mouvement();
    // Initialise les coordonnées et la direction du mouvement
    res->x = s->tete_serpent->pos.x;
    res->y = s->tete_serpent->pos.y;
    res->mv = dern;
    // Ajoute le mouvement à la liste des mouvements du serpent
    ajouter_mouvement_debut_liste(s->move, res);
}
