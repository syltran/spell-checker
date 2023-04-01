#include "Listes.h"
#include "ATR.h"
#include "Lecture.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 25


int main(int argc, char *argv[]){
    verifie_appel(argc, argv);

    FILE *a_corriger, *dico;
    Liste erreurs = NULL;
    ATR A = NULL;
    char *mot;
    char buffer[MAX];
    int i = 0;
    

    a_corriger = ouvre_fichier(argv[1]);
    dico = ouvre_fichier(argv[2]);

    if (!construire_ATR(dico, &A)){
        fprintf(stderr, "A n'a pas pu être construit car un problème d'allocation a eu lieu\n");
        exit(EXIT_FAILURE);
    }
    //afficher_ATR(A, buffer, i);


    mot = (char*) malloc(sizeof(char) * 25);
    /* Algorithm 1 */
    while (fscanf(a_corriger, "%s", mot) != EOF){
        if (mot[strlen(mot) - 1] == '.'){
            mot[strlen(mot) - 1] = '\0';
        }

        if (!rechercher_dans_ATR(A, mot)){ /* si le mot n'est pas dans le dico */
            if (!inserer_en_tete(&erreurs, mot)){
                fprintf(stderr, "Un problème d'allocation a eu lieu\n");
                exit(EXIT_FAILURE);
            }
        }
        mot = (char*) malloc(sizeof(char) * 25);
    }

    printf("Mot(s) mal orthographié(s) :\n");
    afficher_Liste(erreurs);
    return 0;
}