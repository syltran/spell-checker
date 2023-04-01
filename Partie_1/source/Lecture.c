#include "Lecture.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX 25


void verifie_appel(int argc, char **argv){
    if (argc != 3){
        fprintf(stderr, "usage : %s <nom du fichier texte à corriger> <dictionnaire>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}

FILE *ouvre_fichier(const char *nom){
    FILE *f = fopen(nom, "r");
    if (f == NULL){
        fprintf(stderr, "impossible d'ouvrir le fichier %s\n", nom);
        exit(EXIT_FAILURE);
    }
    return f;
}


int construire_ATR(FILE *dico, ATR *A){
    char mot[MAX];

    while (fscanf(dico, "%s", mot) != EOF){
        if (!inserer_dans_ATR(&(*A), mot)){
            return 0;
        }
    }
    return 1;
}
