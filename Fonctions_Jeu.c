#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Fonctions_Jeu.h"
#include "Grille.h"
#include "Liste_Section.h"
#include "Serpent.h"
#include "Liste_Mouvement.h"
#include "Matrice.h"


// Fonction pour vérifier si le serpent a mangé un fruit
int manger(struct grille *p, struct serpent *s,struct matrice *m){
  //if (p->fruit.x == s->tete_serpent->pos.x && p->fruit.y == s->tete_serpent->pos.y) return 1;
  int x = s->tete_serpent->pos.x;
  int y = s->tete_serpent->pos.y;
  
  if( m->tab[x][y] == fruit) return 1;
  return 0;
}




// Fonction pour vérifier si le serpent est sur une case de son propre corps
int est_serpent (struct grille *p, struct serpent *s, struct matrice *m){
  int x = s->tete_serpent->pos.x;
    int y = s->tete_serpent->pos.y;
  // Vérifie si la tête du serpent est sur une case occupée par un serpent
  if( m->tab[x][y]== serp) return 1;
  return 0;
  
}

// Génère une nouvelle position pour le fruit si la position précédente était occupée par le serpent
void nv_tirage(struct grille *p, struct serpent *s, struct matrice *m){
  if (m->tab[p->fruit.x][p->fruit.y] == serp) {
     // Tant que la position du fruit est occupée par le serpent, génère une nouvelle position pour le fruit
    while(m->tab[p->fruit.x][p->fruit.y] == serp){
      grille_tirage_fruit(p);
}
  }
}

// Fonction principale pour faire bouger le serpent sur la grille
void bouger_serpent(struct grille *p,struct serpent *s,struct matrice *m, int delai, int nb_joueur)
{ 

  srand(time(NULL));

  /* Initialisation de ncurses et du clavier(4 lignes)*/
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
   
  int touche;
  int derniere_touche;
  
  do{
    derniere_touche = touche ;
    touche = getch(); 
    
    printf("\33[2J"); // Efface tout l'ecran 
    printf("\33[H");

    mouvement_serpent(s,derniere_touche);// Gère le mouvement du serpent en fonction de la touche précédente


    // Déplacer le serpent en fonction de la touche pressée
    switch (touche){
      
        case KEY_UP:
            s->tete_serpent->pos.x--;//monter
            
            break;
        
        case KEY_DOWN:
          
            s->tete_serpent->pos.x++;//descendre
            
            break;

        case KEY_LEFT:
            s->tete_serpent->pos.y--;//gauche 
           
            break;
        
        case KEY_RIGHT:
        
            s->tete_serpent->pos.y++ ; // droite
            
            break;
    }

    

     // Vérifie si le serpent a atteint les bords de la grille 
    if(s->tete_serpent->pos.x > p->m-1 || s->tete_serpent->pos.y > p->n-1) break;
    if(s->tete_serpent->pos.x < 0 || s->tete_serpent->pos.y < 0) break;
    
    // Vérifie si le serpent est sur une case de son propre corps
    if (est_serpent(p,s,m) == 1) break;


    
    // Vérifie si le serpent a mangé un fruit
    if(manger(p,s,m) == 1) {

      // Génère un nombre aléatoire de nouvelles sections de serpent
      int nombre = rand()%5 +1;
      grille_tirage_fruit(p);// Génère un nouveau fruit sur la grille
      nv_tirage(p,s,m);// Gère le tirage d'une nouvelle position pour le fruit si nécessaire
      grille_vider(p);// Vide la grille
      
      // Ajoute de nouvelles sections au serpent
      for(int i=0; i<nombre; ++i){
        struct section *tmp = creer_section(1);
        tmp ->couleur = couleur_aleatoire();
        ajouter_section_debut_serpent(s,tmp);

        
      }
      
      
    }

      printf("ICI\n");// Indique que le serpent est ici (pour le débogage)
    
    grille_remplir2(p,s,m); // Remplit la grille avec le serpent et le fruit
    fflush(stdout);


  }while ( touche !='q');// Sort de la boucle si la touche 'q' est pressée


  endwin();// Termine l'interface ncurses
  printf("\33[2J"); /* Efface tout l'ecran */
  printf("\33[H");
  printf("\n\n Fin ! \n");// Indique que le jeu est terminé
  desallouer_tete(&s);
  desallouer_liste(&s->move);
  desallouer_serpent(&s);
  grille_desallouer(&p);
  desallouer_matrice(&m);
}