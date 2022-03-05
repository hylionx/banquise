#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

typedef struct{int x ; int y;}position;
typedef struct{int dx ; int dy;}vecteur;

typedef struct{
    int etat;      // 1 = vivant , -1 = piégé , 0 = mort;
    int id;
    char nom[10];
    int couleur;
    position pos;
    vecteur vect;
    int score;
}JOUEUR;

JOUEUR *initJoueurs(int size);        // fonction pour creer un tableau de "size" joueurs

void killJoueur(JOUEUR* j);           // fonction pour tuer un joueur (prends en parametres le joueur et le nombre de joueurs encore disponible)

void classement(JOUEUR* j, int nbr);  // fonction pour afficher le classement des joueurs (prends en parametres le tableau de joueurs et sa taille)


#endif // JOUEUR_H_INCLUDED
