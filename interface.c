#include "main.h"



bool est_dans_premisse(Propositions* premisse, char* ptest){
    Propositions* p = premisse;
    if (est_vide(p)) {
        return false;
    } else if (strcmp(p->proposition, ptest) == 0) {
        return true;
    } else if (p->next != NULL) {
        return est_dans_premisse(p->next, ptest);
    } else {
        return false;
    }
}





BC* lister_base(BC* base){          //retourne un pointeur vers la base choisie
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


BC* get_base_numero(int numero){          //renvoie la base correspondant au numero que l'on donne
    BC* base = bases;
    int i = 1;
    while (base != NULL && i < numero){
        base = bc_suivant(base);
        i++;
    }
    return base;
}


Regle get_regle_numero(BC* base, int numero){          ///renvoie la regle correspondant au numero dans la base
    Regle* regle = base->regles;
    int i = 1;
    while (regle != NULL && i < numero){
        regle = regle_suivant(regle);
        i++;
    }
    return *regle;
}

void supprimer_regle(BC *base, int num_regle){     ////a verif nouveau
    if (base != NULL){
        Regle* regle = base->regles;
        Regle* prev = NULL;
        int i = 1;
        while (regle != NULL && i < num_regle){
            prev = regle;
            regle = regle_suivant(regle);
            i++;
        }
        if (regle != NULL){
            if (prev == NULL){
                base->regles = regle_suivant(regle);
            }
            else {
                prev->next = regle_suivant(regle);
            }
            free(regle);
        }
    }
}



void suprimer_proposition(Regle *regle, char *propo){   ///a verif nouveau
    if (regle != NULL){
        Proposition* p = regle->premisses;
        Proposition* prev = NULL;
        while (p != NULL && strcmp(p->proposition, propo) != 0){
            prev = p;
            p = p->next;
        }
        if (p != NULL){
            if (prev == NULL){
                regle->premisses = p->next;
            }
            else {
                prev->next = p->next;
            }
            free(p);
        }
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


BC *bc_suivant(BC *base){
	if (base != NULL){
		return base->next;
	}
	else
		return NULL;

}

int taille_base(BC *base){   //compte le nombre de regles dans une base
    int taille = 0;
    Regle *regle = base->regles;
    while (regle != NULL){
        taille++;
        regle = regle_suivant(regle);
    }
    printf("La base %s contient %d regles.\n", base->nom, taille);
    return taille;
}



int main() {
    char choix;
    int num_regle;
    int conttinuer = 1;
    int selection = 1;
    int action = 1;
    int taille = 0;
    BC *bases = *lecture_fichier(const char *chemin);
    while (conttinuer == 1){
        ///choix de la base
        while (selection == 1){
            printf("Voulez vous choisir une base ou en creer une nouvelle? (s: selectioner une base, n: nouvelle base)\n");
            choix = getchar();
            if (choix == 's'){
                BC* b = lister_base(*bases);
                liste_regles_base(b);
                taille = taille_base(b);
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
            choix = getchar();
            if (choix == 'o'){
                printf("choisissez une action a effectuer sur cette base\n");
                printf("a: ajouter une regele\n");      ///a verif
                printf("b: modifier une regle\n");      ///a verif avec nouvelle fonction
                printf("c: supprimer une regle\n");     ///a verif avec nouvelle fonction 
                printf("d: afficher les regles\n");     ///a verif
                printf("e: supprimer la base\n");       ///a verif
                printf("f: sauvegarder les bases\n");   ///a verif
                printf("g: moteur inference\n");        ///a verif
                choix = getchar();
                switch (choix){
                    ///ajout d'une regle
                    case 'a':
                        Regle* r = creer_regle();
                        printf("Entrez la conclusion de la regle : ");
                        char conclusion[100];
                        scanf("%s", conclusion);
                        r->conclusion = conclusion;
                        while (p)
                            printf("Entrez la proposition de la regle ou f quand vous avez fini: ");
                            char propo[100];
                            scanf("%s", propo);
                            if (strcmp(propo, "f") == 0){
                                printf("Regle cree : %s => %s\n", r->premisses->proposition, r->conclusion);
                                printf("%d : %s =>", i, regle->conclusion);
                                char *p = regle->premisses->proposition;
                                while (*p != NULL){
                                    printf(" %s", *p);
                                    *p = *p->next;
                                }
                                Ajout_regle(*base, r);
                                break;
                            }
                            else {
                                Ajout_proposition(r, prop);
                            }

                        
                        break;

                    ///modification d'une regle
                    case 'b':
                        printf("quel numero de regle voulez-vous modifier?\n");
                        scanf("%d", &num_regle);
                        if (num_regle > taille || num_regle <= 0){
                            printf("Numero de regle invalide.\n");
                            break;
                        }
                        else{
                            while (modif == 1){
                                printf("quel modification voulez-vous effectuer?\n");
                                *r = get_regle_numero(b, num_regle);
                                printf("modifier la premisse (p), modifier la conclusion (c)\n");
                                choix = getchar();
                                ///modification de la premisse
                                if (choix == 'p'){
                                    printf("a: ajout, s: suppression\n");
                                    choix = getchar();
                                    if (choix == 'a'){
                                        printf("nouvelle premisse a ajouter\n");
                                        char new_premisse[100];
                                        scanf("%s", new_premisse);
                                        Ajout_proposition(r, new_premisse);
                                        printf("Premisse ajoutee.\n");
                                    }
                                    else if (choix == 's'){
                                        printf("quelle premisse voulez-vous supprimer?\n");
                                        char del_premisse[100];
                                        scanf("%s", del_premisse);
                                        Supprimer_proposition(r, del_premisse);    /// a verif nouvelle fonction
                                        printf("Premisse supprimee.\n");
                                    }
                                    else {
                                        printf("Choix invalide.\n");
                                    }
                                    printf("Premisse modifiee.\n");
                                    
                                }

                                ///modification de la conclusion
                                else if (choix == 'c'){
                                    printf("nouvelle conclusion mettre N pour null / la supprimer\n");
                                    char new_conclusion[100];
                                    scanf("%s", new_conclusion);
                                    if (strcmp(new_conclusion, "N") == 0){
                                        new_conclusion = NULL;
                                    }
                                    r->conclusion = new_conclusion;
                                    printf("Conclusion modifiee.\n");
                                }
                                else {
                                    printf("Choix invalide.\n");
                                }

                                printf("voulez vous poursuivre les modifications sur cette regle?(o: oui n: non)\n");
                                choix = getchar();
                                if (choix == 'o'){
                                    modif = 1;
                                }
                                else if (choix == 'n'){
                                    modif = 0;
                                }
                                else {
                                    printf("Choix invalide.\n");
                                }
                            }
                        }
                        break;

                    ///suppression d'une regle
                    case 'c':
                        printf("quel numero de regle voulez-vous supprimer?\n");
                        scanf("%d", &num_regle);
                        if (num_regle > taille || num_regle <= 0){
                            printf("Numero de regle invalide.\n");
                            break;
                        }
                        else{
                            supprimer_regle(b, num_regle);            ///fait nouvelle fonction mais verif quand meme
                            printf("Regle supprimee.\n");
                        }
                        break;

                    ///affichage des regles
                    case 'd':
                        liste_regles_base(b);
                        break;
                    
                    ///suppression de la base
                    case 'e':
                        *supr_bc(b);
                        printf("la base a ete supprimee.\n");
                        action = 0;
                        selection = 1;
                        break;

                    ///sauvegarde des bases
                    case 'f':
                        *Sauvegarde(*bases, /*chemin a modif */);
                        printf("Bases sauvegardees.\n");
                        break;

                    ///moteur d inference
                    case 'g':
                        moteur_inference(b);
                        break;
                    }


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
        choix = getchar();
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
