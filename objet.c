#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "banquise.h"
#include "objet.h"

int temp; // variable temporaire pour la permutation

vecteur tabVect[4] = { {1 , 0} , {0 , 1} , {-1 , 0} , {0 , -1} }; // tableau de vecteurs directeur pour la rotation du marteau dans un sense

//vecteur tabVectInverse[4] = { {0 , -1} , {-1 , 0} , {0 , 1} , {1 , 0} }; // tableau de vecteurs directeur pour la rotation du marteau dans le sense inverse

int x=0 , y=0;   // la position des objets a faire apparaitre

int dx=0 , dy=0; // vecteur de direction

/******************* FAIRE APPARAITRE DES OBJETS ********************/

void spawnGlacon(BANQUISE banquise){

    x = (rand() % (N-2)) +1;
    y = (rand() % (M-2)) +1;

    // le glacon spawn uniquement sur de la glace ou il n'y a pas de joueur
    if((banquise[x][y].element == glace) && (banquise[x][y].jou == NULL) )
        banquise[x][y].element = glacon;

}// Compléxité : O(1)

void spawnMarteau(BANQUISE banquise){

    MARTEAU* mart = (MARTEAU *)malloc(sizeof(MARTEAU));

    x = (rand() % (N-2)) +1;
    y = (rand() % (M-2)) +1;

    mart->axe.x = x;
    mart->axe.y = y;

    mart->tete.x = x+1;
    mart->tete.y = y;

    banquise[mart->axe.x][mart->axe.y].element = axeMarteau;
    banquise[mart->tete.x][mart->tete.y].element = teteMarteau;
    banquise[mart->tete.x][mart->tete.y].marteau = mart;


}// Compléxité : O(1)

void spawnRessort(BANQUISE banquise){

    x = (rand() % (N-2)) +1;
    y = (rand() % (M-2)) +1;

    banquise[x][y].element = ressort;

}// Compléxité : O(1)

void spawnRocher(BANQUISE banquise){

    x = (rand() % (N-2)) +1;
    y = (rand() % (M-2)) +1;

    banquise[x][y].element = rocher;

}// Compléxité : O(1)


/******************* ROTATION DU MARTEAU (ANIMATION) ********************/
void rotateMarteau(BANQUISE banquise, MARTEAU* mart, int dx , int dy){

    // nous aurons besoin de l'indice du vecteur dans "tabVect" de l'orientation actuelle du marteau
    int ind = 0;
    for(int i = 0; i < 4 ;i++){
        if( tabVect[i].dx == dx && tabVect[i].dy == dy ){
            ind = i;
            break;
        }
    }

        // on fait 3 tours de boucle pour bouger la tete du marteau (pour faire un belle animation )
        for(int i = 1 ; i <= 3  ; i++){
                // on parcours le tableau de vecteurs en circulaire
                ind++;
                ind %= 4;

                // on supprime la tete du marteau pour mettre de la glace
                banquise[mart->tete.x][mart->tete.y].element = glace;
                banquise[mart->tete.x][mart->tete.y].marteau = NULL;

                // on MAJ la tete du marteau
                mart->tete.x = mart->axe.x + tabVect[ind].dx;
                mart->tete.y = mart->axe.y + tabVect[ind].dy;

                banquise[mart->tete.x][mart->tete.y].element = teteMarteau;
                banquise[mart->tete.x][mart->tete.y].marteau = mart;

                afficheBanquise(banquise);

                Sleep(50);
    }

}// Compléxité : O(1)

/******************* USAGE DU MARTEAU ********************/
void moveMarteau(BANQUISE banquise ,MARTEAU* mart, int x_g, int y_g){

    // le vecteur directeur ( ou ira le glacon )
    dx = mart->tete.x - mart->axe.x;
    dy = mart->tete.y - mart->axe.y;

    // le glacon doit toucher le marteau uniquement sur la gauche ou la droite de la tete du marteau
    if( !(x_g == (mart->tete.x + dx) && y_g == (mart->tete.y + dy)) ){

        // on fait l'animation du marteau
        rotateMarteau(banquise, mart, dx , dy);

        banquise[mart->tete.x][mart->tete.y].element = glace;

        // la tete du marteau sera a cote du glacon qui la toucher
        mart->tete.x = x_g - dx;
        mart->tete.y = y_g - dy;

        banquise[mart->tete.x][mart->tete.y].element = teteMarteau;
        banquise[mart->tete.x][mart->tete.y].marteau = mart;

        // on frappe le marteau pour aller dans la direction (dx , dy) 90 degrés
        moveGlacon(banquise , x_g , y_g , dx , dy);
    }
}// Compléxité : O(1)

/******************* LE MOUVEMENT DU GLACON ********************/
int moveGlacon(BANQUISE banquise ,int x , int y , int dx , int dy){

    if( (x+dx >= N ||  x+dx < 0 ||  y+dy >= M || y+dy < 0) || (banquise[x+dx][y+dy].element == rocher)){//si on depasse la taille de la banquise ou on touche un rocher
        return 0;// ne rien faire => arreter le glacon
    }

    if(banquise[x+dx][y+dy].element == glacon){       // si le glacon touche un autre glacon
    return moveGlacon(banquise ,x+dx, y+dy , dx , dy);// faire bouger l'autre glacon
    } else

    if(banquise[x+dx][y+dy].element == eau){          // si le glacon tombe dans l'eau

       banquise[x+dx][y+dy].element = glace;          // l'eau deviens de la glace
       banquise[x+dx][y+dy].rat = 2;                  // avec un ratio de 2
       banquise[x][y].element = glace;

    return 0;
    } else

    if(banquise[x+dx][y+dy].element == teteMarteau ){ // si le glacon touche la tete du marteau
       moveMarteau(banquise, banquise[x+dx][y+dy].marteau, x, y);

    return 0;
    } else

    if(banquise[x+dx][y+dy].element == ressort){      // si le glacon touche un ressort
    return moveGlacon(banquise ,x, y , -dx , -dy);
    } else

    if(banquise[x+dx][y+dy].jou != NULL){             // si le glacon arrive sur un joueur
        printf("----------------------------------------------------\n"
               "HA HA !!! %s s'est pris un glacon dans la gueule    \n"
               "----------------------------------------------------\n",banquise[x+dx][y+dy].jou->nom);

        killJoueur(banquise[x+dx][y+dy].jou); // tuer le joueur et decrémenter le nombre de joueurs diponible

    return -1;
    }

    if(banquise[x+dx][y+dy].element == glace){        // si le glacon va sur de la glace
        // faire avancer le glacon d'une case et faire un appelle recursif
        banquise[x+dx][y+dy].element = banquise[x][y].element;
        banquise[x][y].element = glace;
        afficheBanquise(banquise);

    return moveGlacon(banquise ,x+dx, y+dy , dx , dy);
    }

    else{                                             // le glacon traverse les objets


        temp = banquise[x+dx][y+dy].element;

        banquise[x+dx][y+dy].element = banquise[x][y].element;
        banquise[x][y].element = glace;
        afficheBanquise(banquise);

        banquise[x+2*dx][y+2*dy].element = banquise[x+dx][y+dy].element;
        banquise[x+dx][y+dy].element = temp;
        afficheBanquise(banquise);


    return moveGlacon(banquise ,x+dx, y+dy , dx , dy);
    }
}// Compléxité : au pire O(N) , N = la taille de la banquise (si le glacon devait parcourir toute la banquise donc ferait N appel recursifs)


