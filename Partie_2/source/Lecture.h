
#ifndef __LECTURE__
#define __LECTURE__

#include "ATR.h"
#include "Listes.h"
#include "Levenshtein.h"
#include <stdio.h>


void verifie_appel(int argc, char **argv);
FILE *ouvre_fichier(const char *nom);
int construire_ATR(FILE *dico, ATR *A);
Liste mots_mal_orthographie(FILE *a_corriger, ATR A);
Liste correction_orthographique(ATR *A, char *mot);
void afficher_proposition(Liste corrections);

#endif
