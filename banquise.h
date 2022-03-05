#ifndef BANQUISE_H_INCLUDED
#define BANQUISE_H_INCLUDED

#include "joueur.h"

#define N 20
#define M 30

typedef enum{glacon=1, depart=2, eau=3, arrivee=4, ressort=5, rocher=6, axeMarteau=7, teteMarteau=8, verglas = 9, piege=14, glace=15}ELEMENT; // enumération volontaire, correspond au numéro de coueleur

/****** MARTEAU ******/
typedef struct{
    position axe;
    position tete;
}MARTEAU;

typedef struct{
    ELEMENT element;    //le type de la case (eau, glaçon, joueur...)
    int rat;            //le ratio (pour la fonte)
    JOUEUR* jou;        // un pointeur de joueur
    MARTEAU* marteau;   // un pointeur de marteau
}CASE;

typedef CASE **BANQUISE;                           // la banquise est une matrice de CASE

void Color(int couleurDuTexte,int couleurDeFond);  // fonction d'affichage de couleurs

void legende();

void Locate(int x,int y);                          // fonction qui affiche la banquise au debut de la console

void defDepArr(BANQUISE banquise);                 // fonction pour definir le point de depart et d'arrivé dans la banquise

BANQUISE initBanquise();                           // fonction pour creer une banquise a l'etat initial

void fonteBanquise(BANQUISE banquise);             // fonction pour le rechauffement climatique (fait baisser le ratio)

void afficheBanquise(BANQUISE banquise);           // fonction pour afficher la banquise

int TryMove(BANQUISE banquise ,JOUEUR* j, int dx , int dy);     // fonction pour le deplacement d'un joueur sur la banquise


#endif // BANQUISE_H_INCLUDED
