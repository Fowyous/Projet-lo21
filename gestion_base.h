#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

///////////////////////////////////////////////////////////////
//      FONCTIONS DE GESTION DE LA BASE DE CONNAISSANCE      //
///////////////////////////////////////////////////////////////


BC Creer_BC(){
    BC new_BC;
    new_BC.regle = Creer_regle();
    new_BC.next = NULL;
    return new_BC;
}

void Ajout_regle(BC* base, Regle regle){
    BC* new_bc = (BC*)malloc(sizeof(BC));
    new_bc->regle = regle;
   new_bc->next = NULL;

    if (base->next == NULL) {
        base->next = new_bc;
    } else {
        BC* current = base;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_bc;
    }
}

Regle tete_Base(BC* base){
    return base->regle;
}

Regle tete_Base(BC* base){
    return base->regle;
