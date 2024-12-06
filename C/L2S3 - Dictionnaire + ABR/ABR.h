#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tableaux.h"


//plus grand mot existant en anglais
#define plus_long_mot 28 

typedef struct abr * ABR;
typedef struct sommet * SOMMET;
typedef struct liste * LISTE;

struct abr{
    SOMMET sommet;
    ABR fils_gauche;
    ABR fils_droit;
};


struct sommet{
    char * mot;
    int nbr_occurence;
    LISTE position_mot;
};


struct liste{
    int nbr_occurence;
    LISTE suiv;
};




ABR init_ABR(SOMMET sommet);
SOMMET init_SOMMET(char * mot, int nbr_occurence, LISTE position_mot);
LISTE init_LISTE(int num);

LISTE liste_ajouter(LISTE liste, int nbr_occurence);
void liste_afficher(LISTE liste);
void free_liste(LISTE liste);

int pre_lecture(char * T, int taille_T);
char * mot_a_zero(char * mot, int taille_mot);

SOMMET * ajouter_tab(SOMMET * tab_sommet, char ** tableau_mot, int * tab_position, int nbr_mot);
char ** creation_tab_mot(int nbr_mot, int nbr_caracter, char* T, int * tab_position, int * nbr_occurence_totale);
void supprimer_doubles(LISTE liste, char ** tableau_mot, int nbr_mot, int tab_position[]);

/*
char* Tableau_triee_pour_ABR(SOMMET * tab_sommet, int nbr_total_mot_triee, int *i_compteur, int compteur[]);
char plus_petit_ou_plus_grand(SOMMET * tab_sommet, char stock_plus_petit,int i, int *i_compteur, int compteur[]);
*/