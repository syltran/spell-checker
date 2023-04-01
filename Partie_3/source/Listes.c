#include "Listes.h"

#include <stdio.h>
#include <stdlib.h>


Cellule* allouer_Cellule(char *mot){
    Cellule* cell = (Cellule*) malloc(sizeof(Cellule));
    if (cell != NULL){
        cell->mot = mot;
        cell->suivante = NULL;
    }
    return cell;
}


int inserer_en_tete(Liste *L, char *mot){
    Cellule *tete;

    tete = allouer_Cellule(mot);
    if (tete == NULL){
        return 0;
    }

    if (*L == NULL){
        *L = tete;
        return 1;
    }
    tete->suivante = *L;
    *L = tete;
    return 1;
}


void liberer_Liste(Liste *L){
    Cellule *tmp;

    while(*L != NULL){
        tmp = (*L)->suivante;
        free(*L);
        *L = tmp;
    }
}


void afficher_Liste(Liste L){
    Cellule *tmp;
    
    tmp = L;
    while(tmp != NULL){
        printf("%s\n", tmp->mot);
        tmp = tmp->suivante;
    }
}
