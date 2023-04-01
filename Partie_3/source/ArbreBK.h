
#ifndef __ARBRE_BK__
#define __ARBRE_BK__

#include "Listes.h"
#include "Levenshtein.h"
#include <stdio.h>

typedef struct noeudBK{
    char *mot;
    int valeur;
    struct noeudBK *filsG;
    struct noeudBK *frereD;
} NoeudBK, *ArbreBK;


NoeudBK* allouer_noeud(char *mot, int val);
NoeudBK* verifier_arete_enfants(ArbreBK parent, int d);
void inserer_nouvel_enfant(ArbreBK *parent, NoeudBK *enfant);

int inserer_dans_ArbreBK(ArbreBK *A, char *mot);
int rechercher_dans_ArbreBK(ArbreBK A, char *mot, Liste *corrections, int *seuil);
ArbreBK creer_ArbreBK(FILE *dico);
void liberer_ArbreBK(ArbreBK *A);
void afficher_ArbreBK(ArbreBK A, int nb_espace);

#endif