#include "ArbreBK.h"

#include <stdio.h>
#include <stdlib.h>

#define ABS(a) ((a) < 0 ? -(a) : (a))
#define MAX 25


NoeudBK* allouer_noeud(char *mot, int val){
    NoeudBK* noeud = (NoeudBK*) malloc(sizeof(NoeudBK));
    if (noeud != NULL){
        noeud->mot = mot;
        noeud->valeur = val;
        noeud->filsG = noeud->frereD = NULL;
    }
    return noeud;
}


/* si un enfant e du noeud "parent" possède une arête de valuation 
égale à "d" alors on renvoie le noeud e, sinon NULL */
NoeudBK* verifier_arete_enfants(ArbreBK parent, int d){
    ArbreBK e;
    e = parent->filsG;

    while (e != NULL){
        if (e->valeur == d){
            return e;
        }
        e = e->frereD;
    }
    return NULL;
}

/* insère le nouvel enfant "enfant" au noeud "parent" */
void inserer_nouvel_enfant(ArbreBK *parent, NoeudBK *enfant){
    ArbreBK e;

    if ((*parent)->filsG == NULL){ /* si "parent" n'a pas d'enfant */
        (*parent)->filsG = enfant;
        return;
    }

    e = (*parent)->filsG;
    while (e->frereD != NULL){
        /* ce if permet de faire en sorte que la valuation des arêtes 
        soit croissante dans les enfants (e{1}, e{2}, ..., e{n}) :
        v{1} < v{2} < ... < v{n} */
        if (enfant->valeur < e->frereD->valeur){
            enfant->frereD = e->frereD;
            e->frereD = enfant;
            return;
        }
        e = e->frereD;
    }
    e->frereD = enfant;
}


int inserer_dans_ArbreBK(ArbreBK *A, char *mot){
    int d;
    NoeudBK *enfant;

    if (*A == NULL){
        *A = allouer_noeud(mot, 0);
        if (*A == NULL){
            return 0;
        }
    }
    else{
        d = Levenshtein(mot, (*A)->mot);
        enfant = verifier_arete_enfants(*A, d);

        if (enfant == NULL){
            enfant = allouer_noeud(mot, d);
            if (enfant == NULL){
                return 0;
            }
            inserer_nouvel_enfant(&(*A), enfant);
        }
        else{
            /* si on trouve un enfant qui a une arête de valuation égale à "d" 
            alors on procède à une insertion récursive en prenant "enfant" comme racine */
            inserer_dans_ArbreBK(&enfant, mot);
        }
    }
    return 1;
}



int rechercher_dans_ArbreBK(ArbreBK A, char *mot, Liste *corrections, int *seuil){
    NoeudBK *enfant;
    int d;

    if (A == NULL){
        return 0;
    }
    else{
        d = Levenshtein(A->mot, mot);
        if (d <= *seuil){
            if (d < *seuil){
                *seuil = d;
                liberer_Liste(&(*corrections));
            }
            if (!inserer_en_tete(&(*corrections), A->mot)){
                /* erreur d'allocation */
                return 0;
            }
        }
        
        enfant = A->filsG;
        while (enfant != NULL){
            if (ABS(enfant->valeur - d) <= *seuil){
                rechercher_dans_ArbreBK(enfant, mot, corrections, seuil);
            }
            enfant = enfant->frereD;
        }
    }
    return 1;
}



ArbreBK creer_ArbreBK(FILE *dico){
    ArbreBK A = NULL;
    char *mot;

    mot = (char*) malloc(sizeof(char) * MAX);
    if (mot == NULL){
        return NULL;
    }

    while (fscanf(dico, "%s", mot) != EOF){
        if (!inserer_dans_ArbreBK(&A, mot)){
            /* erreur d'allocation */
            return NULL;
        }

        mot = (char*) malloc(sizeof(char) * MAX);
        if (mot == NULL){
            return NULL;
        }
    }
    return A;
}



void liberer_ArbreBK(ArbreBK *A){
    if ((*A)->filsG != NULL){
        liberer_ArbreBK(&(*A)->filsG);
    }
    if ((*A)->frereD != NULL){
        liberer_ArbreBK(&(*A)->frereD);
    }
    free(*A);
    *A = NULL;
}



void afficher_ArbreBK(ArbreBK A, int nb_espace){
    NoeudBK *enfant;
    int i;

    if (A->valeur == 0){ /* la racine (le seul noeud à avoir une arête égale à 0) */
        printf("%s\n", A->mot);
    }

    enfant = A->filsG;
    while (enfant != NULL){
        /* on met le nombre d'espace qu'il faut */
        for (i = 0; i < nb_espace; i++){
            if (A->valeur < 10){
                printf("        ");
            }
            else{
                printf("         ");
            }
        }

        printf("|--%d--> %s\n", enfant->valeur, enfant->mot);
        afficher_ArbreBK(enfant, nb_espace + 1);
        enfant = enfant->frereD;
    }
}