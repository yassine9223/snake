#include <stdio.h>
#include <stdlib.h>

#include "Matrice.h"


struct matrice *creer_matrice(int m, int n){
    struct matrice *nv = malloc ( sizeof (struct matrice));
    if (nv == NULL){
        perror("Matrice non allouée\n");
        exit(EXIT_FAILURE);
    }
    nv->m = m;
    nv->n = n;
    
    nv->tab = malloc (m* sizeof(enum element *));

    if(nv->tab == NULL){
        perror("Premiere dimension non allouée\n");
        exit(EXIT_FAILURE);
    }
    for (int i=0; i<m; ++i){
        nv->tab[i] =  malloc (n * sizeof (enum element));
        if (nv->tab[i] == NULL){
            perror("Dimension 2 non alouée\n");
            exit(EXIT_FAILURE);
        }
    }

    return nv;
}

void desallouer_matrice(struct matrice **m){
    
    if (*m != NULL){
        for (int i=0; i< (*m)->m ; ++i){
            free((*m)->tab[i]);
        }
        free((*m)->tab);
        free(*m);
        *m = NULL;
    }
}

void matrice_vider(struct matrice *m){
    for (int i=0; i<m->m; ++i){
        for (int e=0; e<m->n; ++e){
            m->tab[i][e]= rien;
        }
    }
}

