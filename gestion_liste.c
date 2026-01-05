#include "gestion_liste.h"



bool est_dans_liste_faits(Liste_faits* liste, char* fait_test){
    Liste_faits* p = liste;
    while (p != NULL){
        if (strcmp(p->fait, fait_test) == 0){
            return true;
        }
        p = p->next;
    }
    return false;
}


void Ajout_fait(Liste_faits** liste, char* nouveau_fait){
    if (est_dans_liste_faits(*liste, nouveau_fait)){
        Liste_faits* p = *liste;
        while (p != NULL){
            if (strcmp(p->fait, nouveau_fait) == 0){
                p->nombre_apparition += 1;
                return;
            }
            p = p->next;
        }
    }
    else {
        Liste_faits* nouveau = (Liste_faits*)malloc(sizeof(Liste_faits));
        nouveau->fait = strdup(nouveau_fait);
        nouveau->nombre_apparition = 1;
        nouveau->next = *liste;
        *liste = nouveau;
    }
}


void afficher_liste_faits(Liste_faits* liste){
    Liste_faits* p = liste;
    printf("Liste des faits :\n");
    while (p != NULL){
        printf("- %s\n", p->fait);
        p = p->next;
    }
}


void supprimer_fait(Liste_faits** liste, char* fait_a_supprimer){
    Liste_faits* current = *liste;
    Liste_faits* previous = NULL;

    while (current != NULL){
        if (strcmp(current->fait, fait_a_supprimer) == 0){
            if (current->nombre_apparition > 1){
                current->nombre_apparition -= 1;
                return;
            }
            else {
                if (previous == NULL){
                    *liste = current->next;
                }
                else {
                    previous->next = current->next;
                }
                free(current->fait);
                free(current);
                return;
            }
        }
        previous = current;
        current = current->next;
    }
}


bool est_videliste(Liste_faits* liste){
    if (liste == NULL){
        return true;
    }
    return false;
}


int taille_faits(Liste_faits* liste){
    int taille = 0;
    Liste_faits* p = liste;
    while (p != NULL){
        taille++;
        p = p->next;
    }
    return taille;
}
