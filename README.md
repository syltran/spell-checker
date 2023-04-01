# Projet/DM Correcteur Orthographique

**Auteurs :** Sylvain Tran, Kevin Thai, Lesly Jumelle TOUSSAINT

**Date :** 2022 (L2, semestre 4)

**Objectif :**  
Implémenter en langage C un mini correcteur orthographique en 3 parties.

-La partie 1 a pour but de trouver les mots mal orthographiés d’un texte donné en utilisant un arbre lexicographique implémenté sous forme d’ATR (arbre ternaire de recherche). Cet ATR va servir de "dictionnaire" de référence contenant à priori les mots correctement orthographiés.

-La partie 2 a pout but d’implémenter un algorithme qui va proposer des suggestions de correction pour chaque mot m mal orthographié d’un texte. Cet algorithme consiste à rechercher dans l'ATR l'ensemble des mots m' qui sont à distance de Levenshtein minimale du mot m.

-Dans la partie 3, nous utilisons les arbres BK (Burkhard-Keller) pour faire à la fois la détection des mots mal orthographiés et les propositions de corrections.

**Sujet :**  
Voir le [sujet](https://github.com/syltran/spell-checker/blob/master/sujet_DM-Projet.pdf)

**Détails d'implémentation relatifs à chaque partie :**  
Partie 1 : voir le [rapport](https://github.com/syltran/spell-checker/blob/master/Partie_1/Tran_Thai_Rapport.pdf)  
Partie 2 : voir le [rapport](https://github.com/syltran/spell-checker/blob/master/Partie_2/TRAN_THAI_TOUSSAINT_Rapport.pdf)  
Partie 3 : voir le [rapport](https://github.com/syltran/spell-checker/blob/master/Partie_3/TRAN_THAI_TOUSSAINT_Rapport.pdf)