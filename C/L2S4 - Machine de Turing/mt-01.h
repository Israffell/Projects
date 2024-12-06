#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct Machine{
	char init;   		//état initial
	char accept; 		//état final
	int head; 	 		//position de la tête de lecture
	char* input;      	//mot d'entrée
	int nbr_transition;  //nombre de transitions
	char current_state; //état actuel de la MT
	char* read_state;	//état où on lit la lettre
	char* read_letter;  //lettre à lire
	char* write_state;  //état où on écrit la lettre
	char* write_letter; //lettre à écrire 
	char* shift;   		//déplacement de la tête de lecture (<, > ou -)
	int steps;  		//nombre d'étapes éxcécutées

}MT;

void affichage_mt_01(MT mt);
int lecture_mt_01(int argc, char* argv[], MT mt);
