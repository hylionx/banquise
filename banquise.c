#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#include "banquise.h"
#include "objet.h"

// tableau de chaine de caracteres pour afficher a quoi correspond chaque couleur " utilisé dans la fonction legende() "
const char tabColors[16][16]= {"Cadavre","Glacon","Depart","Eau","Arrivee","ressort","rocher","Axe Marteau","Tete Marteau","Verglas","Joueur 1","Joueur 2","Joueur 3","Joueur 4","Piege","glace"};

/******************* CHANGER LA COULEUR DU TEXTE ET DU BACKGROUD ********************/
void Color(int couleurDuTexte,int couleurDeFond){
  HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}// Compléxité : O(1)

/******************* PLACER LE CURSEUR DANS LA CONSOLE ********************/
void Locate(int x,int y){
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD C;
    C.X=(SHORT)x;
    C.Y=(SHORT)y;
    SetConsoleCursorPosition(H,C);
}// Compléxité : O(1)

/******************* AFFICHER LA LEGENDE ********************/
void legende(){
    Locate( 2*(M+2) ,0); // placer le curseur a coté de la banquise
    printf("--------- palette de couleurs---------");

    for(int i = 0; i<16 ; i++){ // parcourir le tableau "tabColors"
        Locate( 2*(M+2) ,i+3);
        Color(0 , i);           // mettre la couleur du BG a celle qui correspond à celle du tableau
        printf("  ");           // afficher la couleur
        Color(15 , 0);          // remettre la couleur blance sur fond noir
        printf(" ===> %s\n",tabColors[i]); // afficher à quoi correspond la couleur
    }
}// Compléxité : O(1)


/******************* DEFINIR LE POINT DE DEPART ET D'ARRIVE ********************/
void defDepArr(BANQUISE banquise){
     banquise[1][ (rand()%N) ].element = depart; // prendre un point aléatoire sur la 1er ligne
     banquise[N-2][(rand()%N)].element = arrivee;// prendre un point aléatoire sur la dernière ligne
}// Compléxité : O(1)

/******************* CREATION DE LA BANQUISE A L'ETAT INITIAL ********************/
BANQUISE initBanquise(){

    // creation de la banquise
    BANQUISE banquise;
    banquise = (CASE **)malloc(sizeof(CASE *) * N);

    for(int i = 0; i < N; i++)
        banquise[i] = (CASE *)malloc(sizeof(CASE) * M);

    // parcourir la banquiseg
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            banquise[i][j].jou = NULL; // ne mettre aucun joueur

            if(i == 0 || j == 0 || i == N-1 || j == M-1){ // les bords de la banquise sera de l'eau
                banquise[i][j].element = eau;
                banquise[i][j].rat = 0;

            }
            else{
                banquise[i][j].element = glace; // le reste sera de la glace
                banquise[i][j].rat = 2;         // avec un ratio de solidité == 2
            }
         }
    }

    defDepArr(banquise);    // mettre le point de depart et d'arrivé

    spawnRessort(banquise); // poser un ressort
    spawnRocher(banquise);  // poser un rocher
    spawnMarteau(banquise); // poser un marteau

    return banquise;
}// Compléxité : O(N * M) N et M les dimensions de la banquise

/******************* RECHAUFFEMENT CLIMATIQUE ********************/
void fonteBanquise(BANQUISE banquise){
    // prendre un point au hazard sur la banquise
    int i = rand() % N;
    int j = rand() % M;

    // si il y a un glacon sur de la glace avec un ratio de 1
    if( banquise[i][j].element==glacon && banquise[i][j].rat == 1 ){
        banquise[i][j].rat = 2;
        banquise[i][j].element = glace;
    } else {
        banquise[i][j].rat--;
    }

    if(banquise[i][j].rat == 0)
       banquise[i][j].element = eau;

}// Compléxité : O(1)

/******************* AFFICHER LA BANQUISE ********************/
void afficheBanquise(BANQUISE banquise){
    Locate(0,0);

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){

// 2 facons d'afficher

// 1) AFFICHER LA BANQUISE AVEC BG_COLOR
            if(banquise[i][j].jou != NULL){
                Color(0,banquise[i][j].jou->couleur);
                printf("%d ", banquise[i][j].jou->id);
                Color(15,0);
            }
            else {
                Color(banquise[i][j].element,banquise[i][j].element);
                printf("  ");
                Color(15,0);
            }
/*_______________________________________________________________________________________________________*/


/*  2) LA BANQUISE AVEC TXT_COLOR

            Color(banquise[i][j].element,0);
            if(banquise[i][j].jou == NULL)
            printf("|%2d,%2d,%2d|",banquise[i][j].element, banquise[i][j].rat, 0);
            else{
            Color(banquise[i][j].jou->couleur,0);
            printf("|%2d,%2d,%2s|",banquise[i][j].element, banquise[i][j].rat, banquise[i][j].jou->nom);
            }
/*_______________________________________________________________________________________________________*/

        }
    printf("\n");
    }
Locate(0,N+3); // repositionner le curseur de la console 3 espaces plus bas que la banquise

}// Compléxité : O(N * M) N et M les dimensions de la banquise

/******************* DEPLACEMENT DU JOUEUR ********************/
int TryMove(BANQUISE banquise ,JOUEUR* j, int dx , int dy){

    if (banquise[j->pos.x+dx][j->pos.y+dy].element==glacon){// si la case vers ou ce deplace le joueur est un glacon
    j->score += 5; // +5 point pour son score
    return moveGlacon(banquise , j->pos.x , j->pos.y , dx , dy);

    } else

    if(banquise[j->pos.x+dx][j->pos.y+dy].jou != NULL){     // si la case vers ou ce deplace le joueur est deja occupée par un autre joueur
    return 0;                                               // ne rien faire ( passer son tour )
    }

    else{                                                   // deplacer le joueur puis on test ou il a mis les pieds

    j->score++; // +1 point pour son score
    banquise[j->pos.x+dx][j->pos.y+dy].jou = banquise[j->pos.x][j->pos.y].jou; // le pointeur de la case suivante recoit la pointeur de la case actuelle
    banquise[j->pos.x][j->pos.y].jou = NULL; // et la case actuelle recoit NULL ( on deplace le joueur )
    (j->pos.x)+=dx;                          // puis, on modifie le champ pos du joueur
    (j->pos.y)+=dy;

    if(banquise[j->pos.x][j->pos.y].element==eau){           // si le joueur tombe dans l'eau il meurt
        printf("-------------------------------------------------------\n"
               "LOOOOOOOOOOOOOOOOOOOOOSER %s est tomber dans l'eau     \n"
               "-------------------------------------------------------\n",j->nom);

        killJoueur(banquise[j->pos.x][j->pos.y].jou);
        return -1;

        } else

    if (banquise[j->pos.x][j->pos.y].element==arrivee){      // si le joueur est sur la case d'arrivée il gagne
    j->score += 100; // +100 point pour son score
        printf("-------------------------------------------------------\n"
               "WINNEEEEEEEEEEEEEEEEEEEEEEER %s a gagner !!!\a\a\a     \n"
               "-------------------------------------------------------\n\n\n",j->nom);
        return 1;

        } else

    if (banquise[j->pos.x][j->pos.y].element==verglas){      // si le joueur est sur du verglas

        banquise[j->pos.x+dx][j->pos.y+dy].jou = banquise[j->pos.x][j->pos.y].jou;
        banquise[j->pos.x][j->pos.y].jou = NULL;
        (j->pos.x)+=dx;
        (j->pos.y)+=dy;

        return 0;


        } else

    if (banquise[j->pos.x][j->pos.y].element==piege){        // si le joueur tombe sur un piege
            printf("-------------------------------------------------------\n"
                   "MDRRRRRRRRRRRRRRR %s est est tomber dans un piege      \n"
                   "-------------------------------------------------------\n",j->nom);
            j->etat = -1;
        return -1;


        } else {
            afficheBanquise(banquise);
            return 0;
        }
    }
}// Compléxité : O(1)
