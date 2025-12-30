#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

///////////////////////////////////////////////////////////////
//      FONCTIONS DE GESTION DE LA BASE DE CONNAISSANCE      //
///////////////////////////////////////////////////////////////


BC* Creer_BC(BC* bases){//Crée une base et l'ajoute en queue et retourne la nouvelle base.
	BC *new_BC;
    if (bases == NULL){

        new_BC = (BC*)malloc(sizeof(BC));
        new_BC->regle = Creer_regle();
	new_BC->next = NULL;
	bases = new_BC;
	return new_BC;
    }
    else if (bases->next == NULL){
        new_BC = (BC*)malloc(sizeof(BC));
        new_BC->regle = Creer_regle();
        new_BC->next = NULL;
	bases->next = new_BC;
    }
    else {
        new_BC = Creer_BC(bases->next);
    }
    return new_BC;
}

void Ajout_regle(BC* base, Regle* regle){
	Regle* derniere_regle = base->regle;
	while (derniere_regle->next != NULL){
		derniere_regle = derniere_regle->next;
	}
	base->regle->next = regle;
	return;
//	BC* new_bc = (BC*)malloc(sizeof(BC));
//    new_bc->regle = regle;
//   new_bc->next = NULL;

//    if (base->next == NULL) {
//        base->next = new_bc;
//    } else {
//        BC* current = base;
//        while (current->next != NULL) {
//            current = current->next;
//        }
//        current->next = new_bc;
//    }
}

void Ajout_nom_BC(BC* base, char* nom){
	base->nom = nom;
}
Regle* tete_Base(BC* base){
    return base->regle;
}


