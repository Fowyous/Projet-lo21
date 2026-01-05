#include <stdio.h>
#include <termios.h>
#include "main.h"

#define INPUT_MAX 100


void moteur_inference(BC* base){
    Liste_faits* l = base->faits;
    Liste_faits* faits_connus = NULL;
    Liste_faits* faits_certain = NULL;
    char fait[100];
    for (int i = 0; i < taille_faits(base->faits); i++){
        printf("est ce que le fait '%s' est certain? (o: oui, n: non)\n", l->fait);
        char reponse = getchar();
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
                printf("est ce que le fait '%s' est certain? (o: oui, n: non)\n", temp->fait);
                char reponse = getchar();
                if (reponse == 'o'){
                    Ajout_fait(&faits_certain, temp->fait);
                }
            }
            temp = temp->next;
        }
    }
    printf("Inference terminee. Faits connus :\n");
    afficher_liste_faits(faits_certain);
}
























char lire_char(){


	char c = getchar();

	return c;
}

void interface_ajout_regle(){// incomplet in faut la configurer pour ajouter la régle a une base
        Regle new_regle = Creer_regle();
        while (1){
                printf("ajouter une proposition(entrer sans rien ajouter pour passer a l'étape suivante):");
                char *proposition = (char*) malloc(INPUT_MAX * sizeof(char));
                fgets(proposition, sizeof(INPUT_MAX), stdin);
                if(proposition[0] == "\n"){break;}
                Ajout_proposition(new_regle, proposition);
        }
        printf("ajouter une conclusion a la règle");
        char *conclusion = (char*) malloc(INPUTSMAX * sizeof(char));
	fgets(conclusion, sizeof(INPUT_MAX), stdin);
	Conclusion(new_regle, conclusion);

}

void menu_BC(){

}
void menu_principal(){
        printf("\033[H\033[J");// vider le terminal
	printf("choisir une option:\n");
	printf("a. lister les bases de connaissances.\n");
	printf("b. créer une base de connaissance.\n");
	char c = lire_char();
	switch(c){
	case('a'):
		menu_BC();
		break;
	case('b'):
		interface_ajout_regle();
		break;
	case('c'):
		break;//a completer
	default:
		printf("mauvais choix."); //a completer il faut refaire la question aprés un input pas bon
	}
}
int main(){
  menu_principal();
  return 0;

}
