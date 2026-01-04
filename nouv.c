#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct Propositions {
        char* proposition;
        struct Propositions* next;
}Propositions;


typedef struct Regle { 
        char* conclusion;
        Propositions* premisse;
	struct Regle* next;
}Regle;


typedef struct BC{
        char* nom;
        Regle* regle;
        Liste_faits* faits;
        struct BC* next;
}BC;


typedef struct liste_faits {
    char* fait;
    int nombre_apparition;
    struct liste_faits* next;
} Liste_faits;


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


bool est_vide(Liste_faits* liste){
    return liste == NULL;
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











void afficher_regle(Regle *regle){     ///a verif nouveau
    if (regle != NULL){
        printf("Regle : %s =>", regle->conclusion);
        Propositions* p = regle->premisse;
        while (p != NULL){
            printf(" %s", p->proposition);
            p = p->next;
        }
        printf("\n");
    }
}














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
    
