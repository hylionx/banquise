#ifndef OBJET_H_INCLUDED
#define OBJET_H_INCLUDED

#include "joueur.h"

/****** GLACON ******/
typedef struct{
    position pos;
    vecteur vect;
}GLACON;

/****** RESSORT ******/
typedef struct{
    position pos;
}RESSORT;

/****** ROCHER ******/
typedef struct{
    position pos;
}ROCHER;

void spawnGlacon(BANQUISE banquise);
void spawnRessort(BANQUISE banquise);
void spawnMarteau(BANQUISE banquise);
void spawnRocher(BANQUISE banquise);

void rotateMarteau(BANQUISE banquise, MARTEAU* mart, int dx , int dy);

void moveMarteau(BANQUISE banquise ,MARTEAU* mart, int x_g, int y_g);

int moveGlacon(BANQUISE banquise , int x , int y , int dx , int dy);


#endif // OBJET_H_INCLUDED
