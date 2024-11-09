all: serpent_game

Fonctions_Jeu.o: Fonctions_Jeu.c Fonctions_Jeu.h
	gcc -c Fonctions_Jeu.c -o Fonctions_Jeu.o

Grille.o: Grille.c Grille.h
	gcc -c Grille.c -o Grille.o

Liste_Mouvement.o: Liste_Mouvement.c Liste_Mouvement.h
	gcc -c Liste_Mouvement.c -o Liste_Mouvement.o

Liste_Section.o: Liste_Section.c Liste_Section.h
	gcc -c Liste_Section.c -o Liste_Section.o

main.o: main.c
	gcc -c main.c -o main.o

Matrice.o: Matrice.c Matrice.h
	gcc -c Matrice.c -o Matrice.o

Serpent.o: Serpent.c Serpent.h
	gcc -c Serpent.c -o Serpent.o

serpent_game: Fonctions_Jeu.o Grille.o Liste_Mouvement.o Liste_Section.o main.o Matrice.o Serpent.o
	gcc -o serpent_game Fonctions_Jeu.o Grille.o Liste_Mouvement.o Liste_Section.o main.o Matrice.o Serpent.o -lncurses


clean:
	rm -f *.o serpent_game

