#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct valeur * VALEUR;
struct valeur{
    int taille_L;
    int taille_T;
    int nbr_mot;
    int * L;
    char * T;
};

VALEUR tableau(char * nom_fichier);