
#ifndef __LISTES__
#define __LISTES__

typedef struct cellule{
    char *mot;
    struct cellule *suivante;
} Cellule, *Liste;


Cellule* allouer_Cellule(char *mot);
int inserer_en_tete(Liste *L, char *mot);
void liberer_Liste(Liste *L);
void afficher_Liste(Liste L);

#endif