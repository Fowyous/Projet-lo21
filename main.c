#include <stdio.h>
#include <termios.h>
#include "main.h"
char lire_char(){

	struct termios oldt, newt;

	printf("\033[H\033[J");// vider le terminal
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
void menu_principal(){
	printf("choisir une option:\n");
	printf("a. mettre des propositions pour avoir des conclusions.\n");
	printf("b. ajouter une règle.\n");
	char c = lire_char();
	if ( c == 'a'){
		//a completer
	}
	if ( c =='b'){
		//a completer
	}

}
int main(){
  menu_principal();
  return 0;

}
