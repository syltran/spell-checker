#include "Listes.h"
#include "ATR.h"
#include "ArbreBK.h"
#include "Lecture.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 25



int main(int argc, char *argv[]){
    FILE *a_corriger, *dico;
    ArbreBK A;
    Liste erreurs;
    Liste corrections = NULL;
    int seuil;
    Cellule *tmp;
    int temps_debut, temps_fin;

    
    verifie_appel(argc, argv);
    a_corriger = ouvre_fichier(argv[1]);
    dico = ouvre_fichier(argv[2]);


    temps_debut = time(NULL);
    A = creer_ArbreBK(dico);
    if (A == NULL){
        fprintf(stderr, "Erreur d'allocation (Arbre BK A)\n");
        exit(EXIT_FAILURE);
    }
    fclose(dico);
    /* afficher_ArbreBK(A, 0); */
    
    
    /* PARTIE 1 : recherche des mots mal orthographié en parcourant un arbre BK */

    erreurs = mots_mal_orthographie_avec_ArbreBK(a_corriger, A);
    if (erreurs == NULL){
        fprintf(stderr, "Erreur d'allocation (erreurs)\n");
        exit(EXIT_FAILURE);
    }
    fclose(a_corriger);
    /* printf("Mot(s) mal orthographié(s) :\n");
    afficher_Liste(erreurs); */


    /* PARTIE 2 : correction orthographique par recherche approximative de mots identiques dans un arbre BK */

    seuil = 5;
    tmp = erreurs;

    /* Algorithm 2 */
    while (tmp != NULL){
        if (!rechercher_dans_ArbreBK(A, tmp->mot, &corrections, &seuil)){
            fprintf(stderr, "Erreur d'allocation (corrections)\n");
            exit(EXIT_FAILURE);
        }
        
        printf("Mot mal orthographié : %s\n", tmp->mot);
        afficher_proposition(corrections);

        liberer_Liste(&corrections);
        seuil = 5;
        tmp = tmp->suivante;
    }

    temps_fin = time(NULL) - temps_debut;
	printf("Temps d'exécution : %d s\n", temps_fin);

    return 0;
}