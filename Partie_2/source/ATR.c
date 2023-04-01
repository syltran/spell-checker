#include "ATR.h"

#include <stdio.h>
#include <stdlib.h>


ATR creer_ATR_vide(){
    ATR a = (ATR) malloc(sizeof(Noeud));
    if (a != NULL){
        a->gauche = NULL;
        a->fils = NULL;
        a->droit = NULL;
    }
    return a;
}


void liberer_ATR(ATR *A){
    if ((*A)->gauche != NULL){
        liberer_ATR(&(*A)->gauche);
    }
    if ((*A)->fils != NULL){
        liberer_ATR(&(*A)->fils);
    }
    if ((*A)->droit != NULL){
        liberer_ATR(&(*A)->droit);
    }
    free(*A);
    *A = NULL;
}


int inserer_dans_ATR(ATR *A, char *mot){
    if (*A == NULL){
        *A = creer_ATR_vide();
        if (*A == NULL){
            /* problème d'allocation */
            return 0;
        }
        (*A)->c = *mot;

        if (*mot != '\0'){
            inserer_dans_ATR(&(*A)->fils, mot + 1);
        }
    }
    if (*mot < (*A)->c){
        inserer_dans_ATR(&(*A)->gauche, mot);
    }
    if (*mot > (*A)->c){
        inserer_dans_ATR(&(*A)->droit, mot);
    }
    if (*mot == (*A)->c && *mot != '\0'){
        inserer_dans_ATR(&(*A)->fils, mot + 1);
    }
    return 1;
}


void supprimer_dans_ATR(ATR *A, char *mot){
    if (*A == NULL){
        return;
    }
    if (*mot < (*A)->c){
        supprimer_dans_ATR(&(*A)->gauche, mot);
    }
    if (*mot > (*A)->c){
        supprimer_dans_ATR(&(*A)->droit, mot);
    }
    if (*mot == (*A)->c){
        if (*mot != '\0'){
            supprimer_dans_ATR(&(*A)->fils, mot + 1);
        }
        if ((*A)->c == '\0'){
            *A = (*A)->droit;
        }
        else{
            /* si c'est le préfixe d'un autre mot */
            if ((*A)->fils != NULL){
                return;
            }
            else{
                if ((*A)->gauche == NULL && (*A)->droit == NULL){
                    *A = NULL;
                }
                else if ((*A)->gauche == NULL && (*A)->droit != NULL){
                    *A = (*A)->droit;
                }
                else if ((*A)->gauche != NULL && (*A)->droit == NULL){
                    *A = (*A)->gauche;
                }
                else{
                    Noeud *tmp = *A;
                    *A = (*A)->gauche;
                    (*A)->droit = tmp->droit;
                }
            }
        }
    }
}


void afficher_ATR(ATR A, char buffer[], int i){
    if (A != NULL){
        afficher_ATR(A->gauche, buffer, i);

        buffer[i] = A->c;
        if (A->c == '\0'){
            printf("%s\n", buffer);
        }
        else 
            afficher_ATR(A->fils, buffer, i + 1);
        
        afficher_ATR(A->droit, buffer, i);
    }
}


int rechercher_dans_ATR(ATR A, char *mot){
    if (A == NULL){
        return 0;
    }
    if (*mot < A->c){
        return rechercher_dans_ATR(A->gauche, mot);
    }
    if (*mot > A->c){
        return rechercher_dans_ATR(A->droit, mot);
    }
    if (*mot == A->c && *mot != '\0'){
        return rechercher_dans_ATR(A->fils, mot + 1);
    }
    return 1;
}