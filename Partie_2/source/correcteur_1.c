#include "Listes.h"
#include "ATR.h"
#include "Lecture.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 25



int main(int argc, char *argv[]){
    FILE *a_corriger, *dico;
    Liste erreurs, corrections;
    ATR A = NULL;
    char buffer[MAX];
    int i;
    Cellule *tmp;
    
    verifie_appel(argc, argv);
    a_corriger = ouvre_fichier(argv[1]);
    dico = ouvre_fichier(argv[2]);


    if (!construire_ATR(dico, &A)){
        fprintf(stderr, "A n'a pas pu être construit car un problème d'allocation a eu lieu\n");
        exit(EXIT_FAILURE);
    }
    fclose(dico);
    /*i = 0;
    afficher_ATR(A, buffer, i);*/


    /* PARTIE 1 : recherche des mots mal orthographié */

    erreurs = mots_mal_orthographie(a_corriger, A);
    if (erreurs == NULL){
        fprintf(stderr, "Erreur d'allocation (erreurs)\n");
        exit(EXIT_FAILURE);
    }
    fclose(a_corriger);
    /* printf("Mot(s) mal orthographié(s) :\n");
    afficher_Liste(erreurs); */


    /* PARTIE 2 : correction orthographique par force brute */

    tmp = erreurs;

    /* Algorithm 2 */
    while (tmp != NULL){
        corrections = correction_orthographique(&A, tmp->mot);
        if (corrections == NULL){
            fprintf(stderr, "Erreur d'allocation (corrections)\n");
            exit(EXIT_FAILURE);
        }
        
        printf("Mot mal orthographié : %s\n", tmp->mot);
        afficher_proposition(corrections);
        tmp = tmp->suivante;
    }

    return 0;
}