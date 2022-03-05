#include <stdio.h>
#include <stdlib.h>

#include "joueur.h"

extern int JoueursDispo;

/******************* CREATION D'UN TABLEAU DE JOUEURS ********************/
JOUEUR *initJoueurs(int size){

    JOUEUR* joueur =(JOUEUR*)malloc(sizeof(JOUEUR) * size);

    for(int i = 0 ; i < size; i++){
        joueur[i].id = i+1;

        printf("saisir votre nom\n");
        scanf("%s",&joueur[i].nom);

        joueur[i].couleur = i+10;
        joueur[i].etat = 1;
        joueur[i].pos.x = 1;
        joueur[i].pos.y = i+1;
        joueur[i].score = 0;
    }
return joueur;
}// Compléxité : O(1)

/******************* TUER UN JOUEUR ********************/
void killJoueur(JOUEUR* j){
    if(j->etat != 0){          // si le joueur n'est pas déja mort
        j->etat = 0;           // l'etat du joueur passe de vivant a mort
        j->couleur = 0;        // la couleur du joueur deviens noir (cadavre)
        JoueursDispo--;        // le nombre de joueurs diminue
    }
}// Compléxité : O(1)

/******************* TRI DU TABLEAU DE JOUEURS ********************/
//fonction faite dans le TP 3
void triBulles(JOUEUR *tab, int taille){
    JOUEUR temp;
    for(int j = 0; j < taille ; j++){
        for(int i = 0; i < taille-j-1 ; i++){
            if(tab[i].score < tab[i+1].score){
                temp = tab[i];
                tab[i] = tab[i+1];
                tab[i+1] = temp;
            }
        }
    }
}

/******************* AFFICHER LE CLASSEMENT ********************/
void classement(JOUEUR* j , int nbr){
     printf("\n\n\n");
     // structure du tableau
     printf("----------------------------------------\n"
            "         CLASSEMENT DES JOUEURS         \n"
            "----------------------------------------\n"
            "| classement || ID ||   NOM   || SCORE |\n"
            "----------------------------------------\n");

    // tri du tableau
    triBulles(j,nbr);

    // afficher la pasition, l'id, le nom et le score du joueur
    for(int i=0; i < nbr; i++){
        printf("| %d          || %2d || %7s || %5d |\n"
               "----------------------------------------\n",i+1,j[i].id,j[i].nom,j[i].score);
    }

}// Compléxité : O(nbr), nbr = la taille du tableau de joueurs
