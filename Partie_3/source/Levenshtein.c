#include "Levenshtein.h"

#include <stdio.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))


int Levenshtein(char *un, char *deux){
    if (MIN(strlen(un), strlen(deux)) == 0){
        return MAX(strlen(un), strlen(deux));
    }
    else if (un[0] == deux[0]){
        return Levenshtein(un + 1, deux + 1);
    }
    return 1 + MIN(Levenshtein(un + 1, deux), MIN(Levenshtein(un, deux + 1), Levenshtein(un + 1, deux + 1)));
}
