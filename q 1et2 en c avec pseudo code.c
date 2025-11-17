#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//
//_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//structure//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\\
//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//

////////////////////////////////////structure proposition
typedef struct Propositions {
        char* proposition;
        struct Propositions* next;
}Propositions;

///////////////////////////////////structure regle
typedef struct { 
        char* conclusion;
        Propositions* premisse;
}Regle;

///////////////////////////////////chaine de regles
typedef struct BC{ 
        Regle regle;
        struct BC* next;
}BC;


//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//
//_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//fonctions//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\\
//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//

///////////////////////////////////////////////////////////////
//             FONCTIONS DE GESTION DES REGLES               //
///////////////////////////////////////////////////////////////

////////////////////////////////////////////////cree une regle vide
//fonction cree_regle()
//        new_regle <- Regle(NULL, Propositions())
//        cree_regle <- new_regle
//fin

Regle Creer_regle(){
    Regle new_regle;
    new_regle.conclusion = NULL;
    new_regle.premisse = NULL;
    return new_regle;
}



////////////////////////////////////////////////cree une conclusion pour une regle
//fonction cree_conclusion(regle, conclu)
//        si conclusion(regle) != NULL
//                conclusion(regle) <- conclu
//        fin si
//fin

void Conclusion(Regle* regle, char* conclusion){
    if (regle->conclusion != NULL) {
        regle->conclusion = conclusion;
    }
}



////////////////////////////////////////////////verifie si la premisse est vide
//fonction est_vide(premisse)
//        p <- tete(premisse)
//        si proposition(p) != NULL
//                est_vide <- FAUX
//        fin si
//        est_vide <- VRAI
//fin

bool est_vide(Propositions* premisse){
    Propositions* p = premisse;
    if (p->proposition != NULL)
        return false;
    return true;
}



////////////////////////////////////////////////ajout une proposition a la premisse d une regle en queue
//fonction ajout_proposition(premisse, propo)
//        new_proposition <- Proposition(propo)
//        p <- tete(premisse)
//        si est_vide(p)
//                valeur(p) <- propo
//                ajout_proposition <- p                        /!\possiblement inutile
//        fin si
//        tant que non est_vide(suivant(p))
//                p <- suivant(p)
//        fin tant que
//        suivant(p) <- new_proposition
//        ajout_proposition <- p                                /!\possiblement inutile
//fin

void Ajout_proposition(Regle* regle, char* proposition){
    Propositions* new_propo = (Propositions*)malloc(sizeof(Propositions));
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



/////////////////////////////////////////////////renvoie la conclusion d une regle ou NULL si elle n existe pas
//fonction concusion_regle(regle)
//        c <- conclusion(regle)
//        si c == NULL
//                concusion_regle <- NULL ou/et message d'erreur
//        sinon
//                concusion_regle <- c
//        fin si
//fin

char* conclusion_regle(Regle* regle){
    char* c = regle->conclusion;
    if (c == NULL) {
        return NULL; // ou afficher un message d'erreur
    } else {
        return c;
    }
}



////////////////////////////////////////////////renvoie la tete de la premisse ou NULL si elle n existe pas
//fonction tete_premisse(premisse)
//        p <- tete(premisse)
//        si est_vide(p)
//                tete_premisse <- NULL ou/et message d'erreur
//        sinon
//                tete_premisse <- proposition(p)
//        fin si
//fin

char* tete_premisse(Propositions* premisse){
    Propositions* p = premisse;
    if (est_vide(p)) {
        return NULL; // ou afficher un message d'erreur
    } else {
        return p->proposition;
    }
}



////////////////////////////////////////////////verifie si une proposition est dans la premisse
//fonction est_dans_premisse(premisse, ptest)
//        p <- tete(premisse)
//        si est_vide(p)
//                est_dans_premisse <- FAUX
//        sinon si proposition(p) == ptest
//                est_dans_premisse <- Vrai
//        sinon si suivant(p) != NULL
//                est_dans_premisse <- est_dans_premisse(rest(p), ptest)
//        sinon
//                est_dans_premisse <- FAUX
//        fin si
//fin

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


///////////////////////////////////////////////////////////////
//      FONCTIONS DE GESTION DE LA BASE DE CONNAISSANCE      //
///////////////////////////////////////////////////////////////



///////////////////////////////////////////////////cree une base de connaissance vide
//fonction cree_BC()
//        new_BC <- BC(cree_regle(), NULL)
//        cree_BC <- new_BC
//fin

BC Creer_BC(){
    BC new_BC;
    new_BC.regle = Creer_regle();
    new_BC.next = NULL;
    return new_BC;
}



////////////////////////////////////////////////ajout une regle a la base de connaissance en queue
//fonction ajout_regle(base, regle)
//        new_bc <- BC(regle, NULL)
//        bc <- tete(base)
//        si suivant(bc) == NULL
//                suivant(bc) <- new_bc
//        sinon
//                tant que suivant(bc) != NULL
//                        bc <- suivant(bc)
//                fin tant que
//                suivant(bc) <- new_bc
//        fin si
//fin

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


////////////////////////////////////////////////renvoie la regle en tete de la base de connaissance
//fonction tete_Base(base)
//        tete_Base <- regle(tete(base))
//fin

Regle tete_Base(BC* base){
    return base->regle;
}













//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//
//_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//truc test//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\\
//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//



void supr_proposition(Propositions* premisse, char* propo_s){       // supprimer une proposition de la premisse
    if (!est_dans_premisse(premisse, propo_s)) {
        return; // FAUX ou message d'erreur
    } else {
        Propositions* p = premisse;
        Propositions* prev = NULL;
        while (p != NULL) {
            if (strcmp(p->proposition, propo_s) == 0) {
                if (prev == NULL) {
                    // Suppression de la tête
                    premisse = p->next;
                } else {
                    prev->next = p->next;
                }
                free(p);
                return;
            }
            prev = p;
            p = p->next;
        }
    }
    
}










//fonction supr_proposition(premisse, propo_s)
//        si non est_dans_premisse(premisse, propo_s)
//                supr_proposition <- FAUX ou message d'erreur
//        sinon
//                p <- tete(premisse)
//                tant que suivant(p) != NULL
//                        si proposition(p) == propo_s



//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//
//_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//affichage//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\\
//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//

//affichage d'une regle 
void afficher_regle(Regle* regle){
    printf("Conclusion: %s\n", regle->conclusion);
    printf("Premisse: ");
    Propositions* p = regle->premisse;
    while (p != NULL) {
        printf("%s ", p->proposition);
        p = p->next;
    }
    printf("\n");
}


//affichage de la base de connaissance
void afficher_BC(BC* base){
    BC* current = base;
    while (current != NULL) {
        afficher_regle(&(current->regle));
        current = current->next;
    }
}


//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//
//_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//   test  //¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\\
//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//


//valeur de test de chaque fonction
/*  










*/


//code de test global
/*







*/





//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//
//_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//   main  //¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\\
//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//


int main() {
    printf("Projet teste.c compilé avec succès.\n");
    return 0;
}
