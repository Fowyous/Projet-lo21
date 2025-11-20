#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
///////////////////////////////////////////////////////////////
//             FONCTIONS DE GESTION DES REGLES               //
///////////////////////////////////////////////////////////////
Regle Creer_regle(){
    Regle new_regle;
    new_regle.conclusion = NULL;
    new_regle.premisse = NULL;
    return new_regle;
}
void Conclusion(Regle* regle, char* conclusion){
    //if (regle->conclusion != NULL) { //si il est null on la met aussi dedans
    if (regle != NULL){
        regle->conclusion = conclusion;
    }
}

bool est_vide(Propositions* premisse){
    Propositions* p = premisse;
    if (p->proposition != NULL)
        return false;
    return true;
}

void Ajout_proposition(Regle* regle, char* proposition){
//pas besoin d'alloquer une memoire alors qu'on l'a déja alloqué avant
//    Propositions* new_propo = (Propositions*)malloc(sizeof(Propositions));
    new_propo->proposition = proposition;
    new_propo->next = NULL;

    if (est_vide((regle->premisse))) {
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
    char* c = regle->conclusion;
    if (c == NULL) {
        return NULL; // ou afficher un message d'erreur
    } else {
        return c;
    }
}

char* tete_premisse(Propositions* premisse){
    Propositions* p = premisse;
    if (est_vide(p)) {
        return NULL; // ou afficher un message d'erreur
    } else {
        return p->proposition;
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

