#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
///////////////////////////////////////////////////////////////
//             FONCTIONS DE GESTION DES REGLES               //
///////////////////////////////////////////////////////////////
Regle* Creer_regle(Regle *regle){
    Regle *new_regle;
//    if (regle == NULL){
    	new_regle = (Regle*)malloc(sizeof(Regle));
    	new_regle->conclusion = NULL;
    	new_regle->premisse = NULL;
    	new_regle->next = NULL;
//    }/*
    else if (regle->next == NULL){
	Regle* new_regle = (Regle*)malloc(sizeof(Regle));
    	new_regle->conclusion = NULL;
    	new_regle->premisse = NULL;
	regle->next = new_regle;
    }
    else {
    	new_regle = Creer_regle(regle->next);
    }*/
    return new_regle;
}


void Conclusion(Regle* regle, char* conclusion){
	if (regle == NULL){
		printf("regle nulle\n");
		return;
	}
	regle->conclusion = conclusion;

}

bool est_vide(Propositions* premisse){
    Propositions* p = premisse;

    if (p != NULL && p->proposition != NULL){
        return false;
    }
    return true;
}

Regle *Regle_suivant(Regle *regle){
	if (regle != NULL){
		return regle->next;
	}
	else
		return NULL;
}
void Ajout_proposition(Regle* regle, char* proposition){
    Propositions* new_propo = (Propositions*)malloc(sizeof(Propositions));
    new_propo->proposition = proposition;
    new_propo->next = NULL;
    if (regle == NULL){
    	printf("regle est nulle\n");

    }
    if (est_vide(regle->premisse)) {
        regle->premisse = new_propo;
    } else {
        Propositions* current = regle->premisse;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_propo;
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

char* tete_premisse(Regle *regle){
    
//    Propositions* p = regle->premisse;
    if (regle == NULL || est_vide(regle->premisse)) {
        return NULL; // ou afficher un message d'erreur
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

void supr_proposition(Regle *regle){	
	Propositions *propo = regle->premisse->next;
	free(tete_premisse(regle));
	free(regle->premisse);
	regle->premisse = propo;

}
