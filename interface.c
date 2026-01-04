#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct Propositions {
        char* proposition;
        struct Propositions* next;
}Propositions;


typedef struct Regle { 
        char* conclusion;
        Propositions* premisse;
	struct Regle* next;
}Regle;


typedef struct BC{
        char* nom;
        Regle* regle;
        Liste_faits* faits;
        struct BC* next;
}BC;


typedef struct liste_faits {
    char* fait;
    int nombre_apparition;
    struct liste_faits* next;
} Liste_faits;



////////existe deja/////////////////////////////////////////////////////////////// 
char* tete_premisse(Regle *regle){
    if (regle == NULL || est_vide(regle->premisse)) {
        return NULL;
    } else {
        return regle->premisse->proposition;
    }
}


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


char* conclusion_regle(Regle* regle){
    if (regle == NULL){
	printf("regle nulle\n");
	return NULL;
    }
    if (regle->conclusion == NULL){
	printf("conclusion nulle\n");
	return NULL;
    }
    char* c = regle->conclusion;
    if (c == NULL) {
        return NULL; // ou afficher un message d'erreur
    } else {
        return c;
    }
}


BC *bc_suivant(BC *base){
	if (base != NULL){
		return base->next;
	}
	else
		return NULL;
}


Regle* tete_Base(BC* base){
    if (base == NULL || base->regle == NULL){
	return NULL;
    }
    return base->regle;
}


char *nom_bc(BC *base){
	if (base != NULL){
		return base->nom;
	}
}



BC *Sauvegarde(BC *base, const char *chemin){
	FILE *file;
	file = fopen(chemin, "w");
	if (file == NULL){
		printf("Ouverture du fichier impossible!!\n");
		exit(EXIT_FAILURE);
	}
	while (base){
		fprintf(file, "BC: %s\n", nom_bc(base));
		Regle *regle;
		do {
			regle = tete_Base(base);
			if (conclusion_regle(regle) != NULL){
				fprintf(file, "REGL: %s\n", conclusion_regle(regle));
			}
			else 
				break;
			while (tete_premisse(regle) != NULL){
				fprintf(file, "    PROPOS: %s\n", tete_premisse(regle));
				supr_proposition(regle);
			}
			supr_Regle(base);
		}while (regle);
		base = supr_bc(base);
	}
	fclose(file);

}



BC *lecture_fichier(const char *chemin){//lis les bases de connaissances dans le fichier et retourne la tête.
	FILE *file;
	char ligne[350];

        file = fopen(chemin, "r");

        if (file == NULL){
                printf("Ouverture du fichier impossible!!\n");
                exit(EXIT_FAILURE);
        }
	
	BC *tete_base = NULL;
	BC *base = tete_base;
	Regle * nouvel_regle;
	while (fgets(ligne, sizeof(ligne), file) != NULL){
		if (strncmp(ligne, "BC:", 3) == 0) {//ligne contiendera seulement le nom de la base
			if (tete_base == NULL){
				base = Creer_BC(NULL);
				tete_base = base;
			}
			else
			base = Creer_BC(tete_base);

			char * nom_base = strdup(ligne + 4);// on enleve BC: du nom
			nom_base[strlen(nom_base) - 1] = '\0';//on enleve le \n
			Ajout_nom_BC(base, nom_base);
		}
		else if (strncmp(ligne, "REGL:", 5) == 0){
		
			nouvel_regle = Creer_regle(NULL);
			char * conclusion = strdup(ligne + 6);// on enleve REGL:
			conclusion[strlen(conclusion) - 1] = '\0';//on enleve le \n
			Conclusion(nouvel_regle, conclusion);
			Ajout_regle(base, nouvel_regle);
		}
		else if (strncmp(ligne, "    PROPOS:", 11) == 0){
			char *proposition = strdup(ligne + 12);// on enleve le 	PROPOS:
			proposition[strlen(proposition) - 1] = '\0';//on enleve le \n
			Ajout_proposition(nouvel_regle, proposition);
		}
	
	}

	fclose(file);
	return tete_base;
}






////////////////////nouvelle/////////////////////////////////////////////////
Propositions* proposition_suivante(Propositions* propo){
    if (propo != NULL){
        return propo->next;
    }
    else {
        return NULL;
    }
}

BC* choisir_base(BC* base){          //retourne un pointeur vers la base choisie
    int choix_base = -1;
    if (base != NULL){
        printf("choisir parmi les bases avec un numero.\n");
        BC* temp = base;
        int i=1;
        while (temp != NULL){
            printf("%d : %s\n", i, nom_bc(temp));
            temp = bc_suivant(temp);
            i++;
        }
        scanf("%d", &choix_base);
        if (choix_base > 0){
            base = get_base_numero(base, choix_base);
            printf("Base choisie : %s\n", nom_bc(base));
            return base;
        }
    }
    else {
        printf("Base choisie : %s\n", nom_bc(base));
    }
    return base;
}


BC* get_base_numero(BC* bases, int numero){          //renvoie la base correspondant au numero que l'on donne
    BC* base = bases;
    int i = 1;
    while (base != NULL && i < numero){
        base = bc_suivant(base);
        i++;
    }
    return base;
}


Regle* get_regle_numero(BC* base, int numero){          ///renvoie la regle correspondant au numero dans la base
    Regle* regle = tete_Base(base);
    int i = 1;
    while (regle != NULL && i < numero){
        regle = Regle_suivant(regle);
        i++;
    }
    return regle;
}



void supprimer_regle(BC *base, int num_regle){     ////a verif nouveau
    if (base != NULL){
        Regle* regle = tete_Base(base);
        Regle* prev = NULL;
        int i = 1;
        while (regle != NULL && i < num_regle){
            prev = regle;
            regle = Regle_suivant(regle);
            i++;
        }
        if (regle != NULL){
            if (prev == NULL){
                base->regle = Regle_suivant(regle);
            }
            else {
                prev->next = Regle_suivant(regle);
            }
            free(regle);
        }
    }
}



void suprimer_proposition(Regle *regle, char *propo){   ///a verif nouveau
    if (regle != NULL){
        Propositions* p = tete_premisse(regle);
        Propositions* prev = NULL;
        while (p != NULL && strcmp(p->proposition, propo) != 0){
            prev = p;
            p = p->next;
        }
        if (p != NULL){
            if (prev == NULL){
                regle->premisse = p->next;
            }
            else {
                prev->next = p->next;
            }
            free(p);
        }
    }
}


void afficher_regle(Regle *regle){     ///a verif nouveau
    if (regle != NULL){
        printf("Regle : %s =>", conclusion_regle(regle));
        Propositions* p = tete_premisse(regle);
        while (p != NULL){
            printf(" %s", p->proposition);
            p = proposition_suivante(p);
        }
        printf("\n");
    }
}



void liste_regles_base(BC *base){
    if (base != NULL){
        Regle* regle = tete_Base(base);
        int i = 1;
        printf("Regles de la base %s :\n", nom_bc(base));
        while (regle != NULL){
            afficher_regle(regle);
            regle = Regle_suivant(regle);
            i++;
        }
    }
    else {
        printf("Aucune base choisie.\n");
    }
}




int taille_base(BC *base){   //compte le nombre de regles dans une base
    int taille = 0;
    Regle *regle = tete_Base(base);
    while (regle != NULL){
        taille++;
        regle = Regle_suivant(regle);
    }
    printf("La base %s contient %d regles.\n", nom_bc(base), taille);
    return taille;
}



int main() {
    char choix;
    int num_regle;
    int conttinuer = 1;
    int selection = 1;
    int action = 1;
    int taille = 0;
    const char *chemin = "bases.txt";       /////chemin a modif
    BC *bases = lecture_fichier(chemin);        /////chemin a modif
    BC *b = NULL;
    while (conttinuer == 1){
        ///choix de la base
        while (selection == 1){
            printf("Voulez vous choisir une base ou en creer une nouvelle? (s: selectioner une base, n: nouvelle base)\n");
            choix = getchar();
            if (choix == 's'){
                b = choisir_base(bases);
                liste_regles_base(b);
                taille = taille_base(b);
                selection = 0;
            }

            else if (choix == 'n'){
                printf("Creation de nouvelle base non implementee.\n");
                b = Creer_BC(bases);
                printf("Entrez le nom de la nouvelle base : ");
                char nom_base[100];
                scanf("%s", nom_base);
                b->nom = nom_base;
                printf("Base cree : %s\n", nom_bc(b)); 
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
                printf("b: modifier une regle\n");      ///a verif
                printf("c: supprimer une regle\n");     ///a verif
                printf("d: afficher les regles\n");     ///a verif
                printf("e: supprimer la base\n");       ///a verif
                printf("f: sauvegarder les bases\n");   ///a verif
                printf("g: moteur inference\n");        ///a verif
                choix = getchar();
                switch (choix){
                    ///ajout d'une regle
                    case 'a':
                        int ajout = 1;
                        Regle* r = creer_regle();
                        printf("Entrez la conclusion de la regle : ");
                        char conclusion[100];
                        scanf("%s", conclusion);
                        r->conclusion = conclusion;
                        while (ajout == 1)
                            printf("Entrez la proposition de la regle ou f quand vous avez fini: ");
                            char propo[100];
                            scanf("%s", propo);
                            if (strcmp(propo, "f") == 0){
                                printf("Regle cree :\n");
                                afficher_regle(r);
                                Ajout_regle(b, r);
                                ajout = 0;
                                break;
                            }
                            else {
                                Ajout_proposition(r, propo);
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
                            int modif = 1;
                            while (modif == 1){
                                printf("quel modification voulez-vous effectuer?\n");
                                r = get_regle_numero(b, num_regle);
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
                                        r->conclusion = NULL;
                                    }
                                    else {
                                        r->conclusion = strdup(new_conclusion);
                                        free(new_conclusion);
                                    }
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
                        supr_bc(b);
                        printf("la base a ete supprimee.\n");
                        action = 0;
                        selection = 1;
                        break;

                    ///sauvegarde des bases
                    case 'f':
                        Sauvegarde(bases, chemin);       
                        printf("Bases sauvegardees.\n");
                        break;

                    ///moteur d inference
                    case 'g':
                        moteur_inference(b);
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
        choix = getchar();
        if (choix == 'o'){
            Sauvegarde(bases, chemin);
            printf("Bases sauvegardees.\n");
        }
        else if (choix == 'n'){
            printf("Bases non sauvegardees.\n");
        }
    }
    return 0;
}
