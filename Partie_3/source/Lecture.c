#include "Lecture.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 25


void verifie_appel(int argc, char **argv){
    if (argc != 3){
        fprintf(stderr, "usage : %s <nom du fichier texte à corriger> <dictionnaire>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* strstr(c, s) renvoie NULL si la sous-chaine "s" n'est pas dans la chaine principale "c" */
    if (!strstr(argv[1], ".txt")){
        fprintf(stderr, "le nom du fichier texte à corriger doit avoir l'extension '.txt'\n");
        exit(EXIT_FAILURE);
    }

    if (!strstr(argv[2], ".dico")){
        fprintf(stderr, "le dictionnaire doit avoir l'extension '.dico'\n");
        exit(EXIT_FAILURE);
    }
}

FILE *ouvre_fichier(const char *nom){
    FILE *f = fopen(nom, "r");
    if (f == NULL){
        fprintf(stderr, "impossible d'ouvrir le fichier %s\n", nom);
        exit(EXIT_FAILURE);
    }
    return f;
}


int construire_ATR(FILE *dico, ATR *A){
    char mot[MAX];

    while (fscanf(dico, "%s", mot) != EOF){
        if (!inserer_dans_ATR(&(*A), mot)){
            return 0;
        }
    }
    return 1;
}



/* renvoie une liste contenant les mots mal orthographié du texte "a_corriger" 
en utilisant un ATR */
Liste mots_mal_orthographie_avec_ATR(FILE *a_corriger, ATR A){
    Liste erreurs = NULL;
    char *mot;
    
    mot = (char*) malloc(sizeof(char) * MAX);
    if (mot == NULL){
        return NULL;
    }

    /* Algorithm 1 */
    while (fscanf(a_corriger, "%s", mot) != EOF){
        if (!rechercher_dans_ATR(A, mot)){ /* si le mot n'est pas dans le dico */
            if (!inserer_en_tete(&erreurs, mot)){
                /* erreur d'allocation */
                return NULL;
            }
        }
        mot = (char*) malloc(sizeof(char) * MAX);
        if (mot == NULL){
            return NULL;
        }
    }
    return erreurs;
}



/* renvoie une liste contenant les mots mal orthographié du texte "a_corriger" 
en utilisant un arbre BK */
Liste mots_mal_orthographie_avec_ArbreBK(FILE *a_corriger, ArbreBK A){
    Liste erreurs = NULL, tmp = NULL;
    int seuil;
    char *mot;
    
    seuil = 2;
    mot = (char*) malloc(sizeof(char) * MAX);
    if (mot == NULL){
        return NULL;
    }

    /* Algorithm 1 */
    while (fscanf(a_corriger, "%s", mot) != EOF){
        if (!rechercher_dans_ArbreBK(A, mot, &tmp, &seuil)){
            /* erreur d'allocation */
            return NULL;
        }

        if (tmp == NULL || strcmp(tmp->mot, mot) != 0){ /* si le mot n'est pas dans le dico */
            if (!inserer_en_tete(&erreurs, mot)){
                /* erreur d'allocation */
                return NULL;
            }
        }

        mot = (char*) malloc(sizeof(char) * MAX);
        if (mot == NULL){
            return NULL;
        }
        liberer_Liste(&tmp);
        seuil = 2;
    }
    return erreurs;
}



/* renvoie un mot de l'ATR A (celui qui est le plus petit alphabétiquement) */
static void mot_de_ATR(ATR A, char mot[], int i, int *stop){
    if (A != NULL){
        mot_de_ATR(A->gauche, mot, i, stop);

        mot[i] = A->c;
        if (A->c == '\0'){
            *stop = 1;
        }
        else 
            mot_de_ATR(A->fils, mot, i + 1, stop);
        
        if (!*stop){
            mot_de_ATR(A->droit, mot, i, stop);
        }
    }
}

/* renvoie une liste proposant une/des correction(s) du mot "mot" mal orthographié */
Liste correction_orthographique(ATR *A, char *mot){
    Liste corrections = NULL;
    int d, seuil;
    char *m;
    int i, stop;
    ATR tmp = NULL;

    seuil = 5; /* seuil comme on veut */
    i = 0;
    stop = 0;
    m = (char*) malloc(sizeof(char) * MAX);

    if (m == NULL){
        return NULL;
    }

    while(*A != NULL){
        mot_de_ATR(*A, m, i, &stop);

        d = Levenshtein(m, mot);
        if (d <= seuil){
            if (d < seuil){
                seuil = d;
                liberer_Liste(&corrections);
            }
            if (!inserer_en_tete(&corrections, m)){
                /* erreur d'allocation */
                return NULL;
            }
        }
        /* à chaque fois qu'on récupère un mot de l'ATR A, on le supprime.. */
        supprimer_dans_ATR(&(*A), m);
        /* ..et on l'ajoute dans tmp */
        inserer_dans_ATR(&tmp, m);

        m = (char*) malloc(sizeof(char) * MAX);
        if (m == NULL){
            return NULL;
        }
        stop = 0;
    }
    *A = tmp;
    return corrections;
}



/* affiche les propositions de correction */
void afficher_proposition(Liste corrections){
    Liste tmp;
    tmp = corrections;

    printf("Proposition(s) : ");
    while(tmp->suivante != NULL){
        printf("%s, ", tmp->mot);
        tmp = tmp->suivante;
    }
    printf("%s\n", tmp->mot);
}
