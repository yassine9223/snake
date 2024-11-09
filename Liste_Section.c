

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Serpent.h"
#include "Liste_Section.h"
#include "Grille.h"




struct section * creer_section(int longueur){

  srand(time(NULL));
struct section * s = malloc(sizeof(struct section));
  s->couleur = malloc (8 * sizeof(char));
  s->suivant = NULL;
  s->longueur = longueur;
  return s;
}
  

void ajouter_section_debut_serpent(struct serpent *l,struct section *m){
  if (est_vide_serpent(l)) 
    {  
        l->derniere_sec = m; 
    }
  m->suivant = l->premiere_sec;
  l->premiere_sec = m;
  ++l->longueur_serpent;
}

// void ajouter_section_fin_serpent(struct serpent *l,struct section *m){
//    m->suivant = NULL;
//   if (est_vide_serpent(l)) {
//     l->premiere_sec = m;
//   }
//   else {
//   l->derniere_sec->suivant = m;
//   }
//   l->derniere_sec = m;
//   ++l->longueur_serpent;
// }




void detruire_section(struct section **m){
  if ((*m) != NULL){
    free(*m);
    *m = NULL;
  
}
}


char * couleur_aleatoire(){
  srand(time(NULL));
  int n = rand() %110;

  if (n<=10) return ROUGE;
  if (n>10 && n<=30) return VERT;
  if (n>30 && n<=50) return JAUNE;
  if (n>50 && n<=75) return BLEU;
  if (n>75 && n<= 85) return VIOLET;
  if (n>85 && n<=96) return CYAN;
  if (n>96) return BLANC;
  return "a";
}