#include <stdio.h>
#include <termios.h>
#include "main.h"

#define INPUT_MAX 100
char lire_char(){

	struct termios oldt, newt;
	// Obtenir les parametres du terminal
	tcgetattr(0, &oldt);
	newt = oldt;

	//enlever le besoin de faire entrer et l'impression de la lettre sur l'ecran
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &newt);
	char c = getchar();

	//remettre les parametre comme ils etaient
	tcsetattr(0, TCSANOW, &oldt);
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
