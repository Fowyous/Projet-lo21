#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "gestion_regle.h"

///////////////////////////////////////////////////////////////
//      FONCTIONS DE GESTION DE LA BASE DE CONNAISSANCE      //
///////////////////////////////////////////////////////////////


BC* Creer_BC(BC* bases){//Crée une base et l'ajoute en queue et retourne la nouvelle base.
	BC *new_BC;
    if (bases == NULL){
        new_BC = (BC*)malloc(sizeof(BC));
	new_BC->regle = NULL;
	new_BC->next = NULL;
    }
    else if (bases->next == NULL){
        new_BC = (BC*)malloc(sizeof(BC));
        new_BC->regle = NULL;
        new_BC->next = NULL;
	bases->next = new_BC;
    }
    else {
        new_BC = Creer_BC(bases->next);
    }
    return new_BC;
}


BC *bc_suivant(BC *base){
	if (base != NULL){
		return base->next;
	}
	else
		return NULL;

}

char *nom_bc(BC *base){
	if (base != NULL){
		return base->nom;
	}

}
void Ajout_regle(BC* base, Regle* regle) {
    Regle* derniere_regle = base->regle;
    
    if (derniere_regle == NULL) {
        // Base rule list is empty, add the new rule
        base->regle = regle;
        regle->next = NULL;  // Initialize next to NULL
        return;
    }

    // Traverse to the end of the list
    while (derniere_regle->next != NULL) {
        derniere_regle = derniere_regle->next;
    }

    // Link the new rule at the end
    derniere_regle->next = regle;
    regle->next = NULL;  // Initialize next to NULL
}


void Ajout_nom_BC(BC* base, char* nom){
	base->nom = nom;
}
Regle* tete_Base(BC* base){
    if (base == NULL || base->regle == NULL){
	return NULL;
    }
    return base->regle;
}

void supr_Regle(BC *base){
	if (base == NULL || base->regle == NULL){
		return;
	}
	while (tete_premisse(tete_Base(base))){// si la regle n'a plus de premisse on continue
		supr_proposition(tete_Base(base));
	}
	Regle *regle = tete_Base(base);
	base->regle = regle->next;
	free(conclusion_regle(regle));
	free(regle);
}


void supprimer_regle(BC *base, int num_regle){     ////a verif nouveau       a mettre avec celle d avant
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



BC *supr_bc(BC *base){
	if (base == NULL){
		return NULL;
	}
	while (tete_Base(base)){
		supr_Regle(base);
	}
	BC *base2 = base->next;
	free(nom_bc(base));
	free(base);
	return base2;
}


int taille_base(BC *base) {
    int taille = 0;
    Regle *regle = tete_Base(base);
    while (regle != NULL) {
        taille++;
        regle = Regle_suivant(regle);
    }
    printf("La base %s contient %d regles.\n", nom_bc(base), taille);   ////////////peut etre a tege
    return taille;
}


void liste_regles_base(BC *base) {
    if (base != NULL) {
        Regle* regle = tete_Base(base);
        int i = 1;
        printf("Regles de la base %s :\n", nom_bc(base));
        while (regle != NULL) {
            afficher_regle(regle);
            regle = Regle_suivant(regle);
            i++;
        }
    }
    else {
        printf("Aucune base choisie.\n");
    }
}


Regle* get_regle_numero(BC* base, int numero) {
    Regle* regle = tete_Base(base);
    int i = 1;
    while (regle != NULL && i < numero) {
        regle = Regle_suivant(regle);
        i++;
    }
    return regle;
}


BC* get_base_numero(BC* bases, int numero) {
    BC* base = bases;
    int i = 1;
    while (base != NULL && i < numero) {
        base = bc_suivant(base);
        i++;
    }
    return base;
}
