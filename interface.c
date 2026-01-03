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
            while (regle->premisses->proposition != NULL){
                printf(" %s", regle->premisses->proposition);
                regle->premisses->proposition = regle->premisses->proposition->next;
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





int main() {
    char choix;
    while (conttinuer == 1){
        printf("Voulez vous choisir une base ou en creer une nouvelle? (s: selectioner une base, n: nouvelle base)\n");
        scanf(" %c", &choix);
        if (choix == 's'){
            BC* base = lister_base(NULL);
            liste_regles_base(base);
        }

        else if (choix == 'n'){
            printf("Creation de nouvelle base non implementee.\n");
            b = create_base();
            printf("Entrez le nom de la nouvelle base : ");
            char nom_base[100];
            scanf("%s", nom_base);
            b->nom = nom_base;
            printf("Base cree : %s\n", b->nom); 
            ///ajouter la base a la liste des bases
        }

        else {
            printf("Choix invalide.\n");
        }


        return 0;
    }
}
