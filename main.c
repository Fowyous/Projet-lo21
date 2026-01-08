#include <stdio.h>
#include <termios.h>
#include "main.h"

#define INPUT_MAX 100


BC* choisir_base(BC* base){          //Prend en parametre un pointeur vers la tete de la liste de bases, et retourne un pointeur vers la base choisie.
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



void moteur_inference(BC* base){
    Liste_faits* l = base->faits;
    Liste_faits* faits_connus = NULL;
    Liste_faits* faits_certain = NULL;
    char fait[100];
    for (int i = 0; i < taille_faits(base->faits); i++){
        printf("est ce que le fait '%s' est certain? (o: oui, n: non)\n", l->fait);
        char reponse = '\n';
	fflush(stdin);
	while (getchar() != '\n');
	reponse = getchar();
        if (reponse == 'o'){
            Ajout_fait(&faits_certain, l->fait);
        }
        l = l->next;
    }
    //voir si des regles peuvent etre appliquees
    bool nouvelle_inference = true;
    while (nouvelle_inference){
        nouvelle_inference = false;
        Regle* r = base->regle;
        while (r != NULL){
            bool toutes_premisses_connues = true;
            Propositions* p = r->premisse;
            while (p != NULL){
                if (!est_dans_liste_faits(faits_certain, p->proposition)){
                    toutes_premisses_connues = false;
                    break;
                }
                p = p->next;
            }
            if (toutes_premisses_connues && !est_dans_liste_faits(faits_certain, r->conclusion)){
                printf("La regle suivante peut etre appliquee : ");
                afficher_regle(r);
                printf("Conclusion : %s\n", r->conclusion);
                Ajout_fait(&faits_connus, r->conclusion);
                printf("Le fait '%s' a ete ajoute aux faits connus.\n", r->conclusion);
                nouvelle_inference = true;
            }
            r = r->next;
        }
        //demander a l'utilisateur si les faits connus sont certains
        Liste_faits* temp = faits_connus;
        while (temp != NULL){
            if (!est_dans_liste_faits(faits_certain, temp->fait)){
                printf("Le fait '%s' est certain\n", temp->fait);
		while (getchar() != '\n');
                char reponse = getchar();
                    Ajout_fait(&faits_certain, temp->fait);
            }
            temp = temp->next;
        }
    }
    printf("Inference terminee. Faits connus :\n");
    afficher_liste_faits(faits_certain);
}





void principal() {
    char choix;
    int num_regle;
    int conttinuer = 1;
    int selection = 1;
    int action = 1;
    int taille = 0;
    const char *chemin = "bases.txt";       /////chemin a modif si utilisation du autre fichier
    BC *bases = lecture_fichier(chemin);
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
	    scanf(" %c", &choix);
            if (choix == 'o'){
                printf("choisissez une action a effectuer sur cette base\n");
                printf("a: ajouter une regele\n"); 
                printf("b: modifier une regle\n");      ///a verif
                printf("c: supprimer une regle\n");
                printf("d: afficher les regles\n");     ///a verif
                printf("e: supprimer la base\n");       ///a verif
                printf("f: sauvegarder les bases\n");   ///a verif
                printf("g: moteur inference\n");        ///a verif
	    	scanf(" %c", &choix);
                switch (choix){
                    ///ajout d'une regle
                    case 'a':
                        int ajout = 1;
                        Regle* r = Creer_regle();
                        printf("Entrez la conclusion de la regle : ");
                        char conclusion[100];
                        scanf("%s", conclusion);
                        r->conclusion = conclusion;
			getchar();
                        while (ajout == 1){
                            printf("Entrez la proposition de la regle ou f quand vous avez fini: ");
                            char propo[100];
			    fflush(stdin);
			    fgets(propo, sizeof(propo), stdin);
			    propo[strlen(propo) - 1] = '\0';
                            if (strcmp(propo, "f") == 0){
                                printf("Regle cree :\n");
                                afficher_regle(r);
                                Ajout_regle(b, r);
                                ajout = 0;
                                break;
                            }
                            else {
				char *temp = malloc(strlen(propo) + 1);
				if (temp == NULL){
					printf("erreure d'allocation de memoire.\n");
					exit(EXIT_FAILURE);
				}
				strcpy(temp, propo);
                                Ajout_proposition(r, temp);
                            }
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
	    			scanf(" %c", &choix);
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
                                        suprimer_proposition(r, del_premisse);    /// a verif nouvelle fonction
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
                                    }
                                    printf("Conclusion modifiee.\n");
                                }
                                else {
                                    printf("Choix invalide.\n");
                                }

                                printf("voulez vous poursuivre les modifications sur cette regle?(o: oui n: non)\n");
				choix = '\n';
				while (choix == '\n')
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
        printf("voulez vous sauvegarder?(o: oui, n: non)\n");
	choix = '\n';
	while (choix == '\n')
	        choix = getchar();
        if (choix == 'o'){
            Sauvegarde(bases, chemin);
            printf("Bases sauvegardees.\n");
        }
        else if (choix == 'n'){
            printf("Bases non sauvegardees.\n");
        }
    }
    while (bases != NULL){
	    printf("here\n");
	bases = supr_bc(bases);
    }
    return;
    }
}











int main(){
  principal();
  return 0;
}
