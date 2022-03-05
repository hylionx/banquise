#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include "banquise.h"
#include "joueur.h"
#include "objet.h"


/**************** TOUTES LES FONCTIONS DU JEU ONT ETE FAITE PAR LES DEUX MEMBRES DU BINOME "ASSOGBA ET ASMA" ****************/

int JoueursDispo; // le nombre de joueur
int random;       // variable pour spawnGlacon par hazard


void initGame(){

    BANQUISE banquise = initBanquise();

    int nbr;
    printf("saisir le nombre de joueurs\n");
    scanf("%d",&nbr);
    JOUEUR* joueur = initJoueurs(nbr);

    for(int i = 0 ; i < nbr ; i++)         // positionner les joueurs
        banquise[1][i+1].jou = &joueur[i];

    system("cls"); // clear la console pour afficher la banquise




    /******** spawn volontairement ce qu'on veut pour le test *********/
    /*

    banquise[4][1].element = glacon;
    banquise[4][3].element = glacon;
    banquise[6][2].element = glacon;
    banquise[4][2].element = ressort;
    banquise[2][14].element = rocher;

    */


    legende();  // afficher la pallette de couleurs pour se retrouver dans le jeu


    char touche = '0';     // variable pour le deplacement du joueur ( Z , Q , S, D )
    int win = 0;           // variable pour savoir si il y a un gagnant
    int ind = 0;           // variable pour faire jouer a l'indice " ind "
    JoueursDispo = nbr;

    while(touche != '\033' && win != 1 && JoueursDispo > 0){ // 033 = ECHAP , win !=1 => pas encore de gagnant , JoueursDispo > 0 => au moin 1 joueur encore vivant

        // 1 chance sur 20 pour faire apparaitre un glacon
        random = rand() % 20;
        if (random == 1)
            spawnGlacon(banquise);


        fonteBanquise(banquise);
        afficheBanquise(banquise);

        if(joueur[ind].etat == 0 || joueur[ind].etat == -1){  // si le joueur est mort ou piégé

            if(joueur[ind].etat == -1)                        // seulement si le joueur est piégé
               joueur[ind].etat = 1;                          // libérer le joueur pour le tour suivant

            ind ++;                                           // passer au joueur suivant
            ind %= nbr;                                       // modulo le nombre de joueurs, pour retourner au 1er joueur


        }
        else{
                fflush(stdin);           // vider le buffer de getch() pour eviter de saturer la memoire
                touche = getch();       // prendre la direction du joueur

                switch(touche){         // en fonction de la touche, executer le mouvement du joueur

                case 'q':
                    win = TryMove(banquise, &joueur[ind] , 0, -1);
                    break;

                case 'd':
                    win = TryMove(banquise, &joueur[ind], 0, 1);
                    break;

                case 'z':
                    win = TryMove(banquise, &joueur[ind], -1, 0);
                    break;

                case 's':
                    win = TryMove(banquise, &joueur[ind], 1, 0);
                    break;

                default:
                    break;
            }
            ind++;           // on passe au joueur suivant
            ind %= nbr;      // modulo le nombre de joueurs, pour retourner au 1er joueur
        }
    }

    afficheBanquise(banquise);

    if(JoueursDispo == 0)
       printf("\n\n\n-------------- TOUT LE MONDE EST MORT ): --------------\a");

    classement(joueur, nbr);
}


int main(){
    // faire appel a la fonction srand()
    srand(time(NULL));

    // lancer le jeu
    initGame();

    // proposer de rejouer
    int choix;
    printf("\nRefaire la partie ??? (tappez 0 si non)\n");
    scanf("%d",&choix);

    if(choix == 0)
        return 0;
    else
        return main();

}

