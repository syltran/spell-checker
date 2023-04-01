
#ifndef __LECTURE__
#define __LECTURE__

#include "ATR.h"
#include <stdio.h>


void verifie_appel(int argc, char **argv);
FILE *ouvre_fichier(const char *nom);
int construire_ATR(FILE *dico, ATR *A);

#endif
