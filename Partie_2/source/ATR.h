
#ifndef __ATR__
#define __ATR__

typedef struct noeud{
    char c;
    struct noeud *gauche, *fils, *droit;
} Noeud, *ATR;


ATR creer_ATR_vide();
void liberer_ATR(ATR *A);
int inserer_dans_ATR(ATR *A, char *mot);
void supprimer_dans_ATR(ATR *A, char *mot);
void afficher_ATR(ATR A, char buffer[], int i);


int rechercher_dans_ATR(ATR A, char *mot);

#endif