#include "main.h"

BC* lister_base(BC* base){     //retourne le tete de la base choisie
    int choix_base = -1;
    if (base == NULL){
        printf("choisir parmi les bases avec un numero.\n");
        int i=1;
        while (base != NULL){
            printf("%d : %s\n", i, base->nom);
            base = bc_suivant(base);
            i++;
        }
        scanf("%d", &choix_base);
        if (choix_base > 0){
            base = get_base_numero(choix_base);
            printf("Base choisie : %s\n", base->nom);
            return base;
        }
    }
    else {
        printf("Base choisie : %s\n", base->nom);
    }
}



void liste_regles_base(BC *base){
    if (base != NULL){
        Regle* regle = base->regles;
        int i = 1;
        printf("Regles de la base %s :\n", base->nom);
        while (regle != NULL){
            printf("%d : %s =>", i, regle->conclusion);
            while (regle->premisses != NULL){
                printf(" %s", regle->premisses->proposition);
                regle->premisses = regle->premisses->next;
            }
            printf("\n");
            regle = regle_suivant(regle);
            i++;
        }
    }
    else {
        printf("Aucune base choisie.\n");
    }
}


void get_base _numero(int numero){
    BC* base = bases;
    int i = 1;
    while (base != NULL && i < numero){
        base = bc_suivant(base);
        i++;
    }
    return base;
}
