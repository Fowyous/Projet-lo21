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
    int num_regle;
    int conttinuer = 1;
    int selection = 1;
    int action = 1;
    BC *bases = *lecture_fichier(const char *chemin);
    while (conttinuer == 1){
        ///choix de la base
        while (selection == 1){
            printf("Voulez vous choisir une base ou en creer une nouvelle? (s: selectioner une base, n: nouvelle base)\n");
            scanf(" %c", &choix);
            if (choix == 's'){
                BC* b = lister_base(*bases);
                liste_regles_base(b);
                selection = 0;
            }

            else if (choix == 'n'){
                printf("Creation de nouvelle base non implementee.\n");
                b = Creer_BC(*bases);
                printf("Entrez le nom de la nouvelle base : ");
                char nom_base[100];
                scanf("%s", nom_base);
                b->nom = nom_base;
                printf("Base cree : %s\n", b->nom); 
                selection = 0;
            }

            else {
                printf("Choix invalide.\n");
            }            
        }

        ///choix de l'action a effectuer sur la base
        while (action == 1){
            printf("Voulez vous effectuer une action sur cette base? (o: oui, n: non ferme programme, c: changer de base)\n");
            scanf(" %c", &choix);
            if (choix == 'o'){
                printf("choisissez une action a effectuer sur cette base\n");
                printf("a: ajouter une regele\n");
                printf("b: modifier une regle\n");
                printf("c: supprimer une regle\n");
                printf("d: afficher les regles\n");
                printf("e: supprimer la base\n");
                scanf(" %c", &choix);
                switch (choix){
                    case 'a':
                        printf("Ajouter une regle non implemente.\n");
                        break;

                    case 'b':
                        printf("quel numero de regle voulez-vous modifier?\n");
                        scanf("%d", &num_regle);
                        printf("quel modification voulez-vous effectuer?\n");
                        printf("modifier la premisse (p), modifier la conclusion (c)\n");
                        scanf(" %c", &choix);
                        if (choix == 'p'){
                            printf("Modifier la premisse non implemente.\n");
                        }
                        else if (choix == 'c'){
                            printf("Modifier la conclusion non implemente.\n");
                        }
                        else {
                            printf("Choix invalide.\n");
                        }
                        
                        break;

                    case 'c':
                        printf("Supprimer une regle non implemente.\n");
                        supr_Regle(BC *base);
                        break;

                    case 'd':
                        liste_regles_base(b);
                        break;

                    case 'e':
                        printf("la base a ete supprimee.\n");
                        *supr_bc(b);
                        action = 0;
                        selection = 1;
                        break;

                    default:
                        printf("Choix invalide.\n");
                        break;
                }
                action = 0;
            }

            else if (choix == 'n'){
                conttinuer = 0;
                action = 0;
            }

            else if (choix == 'c'){
                selection = 1;
                action = 0;
            }

            else {
                printf("Choix invalide.\n");
            }

        ///sauvegarde des bases avant de quitter
        printf("voulez vous souvgarder?(o: oui, n: non)\n");
        scanf(" %c", &choix);
        if (choix == 'o'){
            *Sauvegarde(*bases, /*chemin a modif */);
            printf("Bases sauvegardees.\n");
        }
        else if (choix == 'n'){
            printf("Bases non sauvegardees.\n");
        }
         
    }
    return 0;
}
