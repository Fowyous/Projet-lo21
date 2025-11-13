#include <stdbool.h>

typedef struct Premisse {
        char* proposition;
        struct Premisse* next;
}Premisse;

typedef struct { 
        char* conclusion;
        Premisse premisse;
}Regle;

typedef struct BC{ 
        Regle regle;
        struct BC* next;
}BC;



//ou variante 


typedef struct Propositions {
        char* proposition;
        struct Propositions* next;
}Premisse;

typedef struct { 
        char* conclusion;
        Propositions* premisse;
}Regle;

typedef struct BC{ 
        Regle regle;
        struct BC* next;
}BC;

//fonction en ALGO
//
//fonction cree_regle()
//        new_regle <- Regle(NULL, Propositions())
//        cree_regle <- new_regle
//fin
//
//
//fonction cree_conclusion(regle, conclu)
//        si conclusion(regle) != NULL
//                conclusion(regle) <- conclu
//        fin si
//fin
//
//
//fonction est_vide(premisse)
//        p <- tete(premisse)
//        si proposition(p) != NULL
//                est_vide <- FAUX
//        fin si
//        est_vide <- VRAI
//fin
//
//
//fonction ajout_proposition(premisse, propo)
//        p <- tete(premisse)
//        si est_vide(p)
//                valeur(p) <- propo
//                ajout_proposition <- p                        /!\possiblement inutile
//        fin si
//        new_proposition <- Proposition(propo)
//        tant que non est_vide(suivant(p))
//                p <- suivant(p)
//        fin tant que
//        suivant(p) <- new_proposition
//        ajout_proposition <- p                                /!\possiblement inutile
//fin
//
//
//fonction tete_premisse(premisse)
//        p <- tete(premisse)
//        si est_vide(p)
//                tete_premisse <- NULL ou/et message d'erreur
//        sinon
//                tete_premisse <- proposition(p)
//        fin si
//fin
//
//
//fonction concusion_regle(regle)
//        c <- conclusion(regle)
//        si c == NULL
//                concusion_regle <- NULL ou/et message d'erreur
//        sinon
//                concusion_regle <- c
//        fin si
//fin
//
//
//fonction est_dans_premisse(premisse, ptest)
//        p <- tete(premisse)
//        si est_vide(p)
//                est_dans_premisse <- FAUX
//        sinon si proposition(p) == ptest
//                est_dans_premisse <- Vrai
//        sinon si suivant(p) != NULL
//                est_dans_premisse <- est_dans_premisse(rest(p))
//        sinon
//                est_dans_premisse <- FAUX
//        fin si
//fin
//                





Regle Creer_regle();        //cree une regle vide
Regle Ajout_premisse(Regle regle, char* proposition);        //ajout une proposition a la premisse d une regle en queu
Regle Conclusion(Regle regle, char* conclusion);        //cree la conclusion d une regle
bool est_dans_premisse(Premisse premisse, char* proposition);        //Tester si une proposition appartient à la prémisse d’une règle, de manière récursive
Premisse supr_propositio(Premisse premisse, char* proposition);        //il faut verif que la propo est dans la premisse
bool est_vide(Premisse premisse);
char* tete_premisse(Premisse premisse);        //revoie la tete de la premisse 
char* conclusion_regle(Regle regle);        //renvoie la conclusion d une regle




BC Creer_BC();        //cree une base vide
BC Ajout_regle(BC base, Regle regle);        //ajout en queu la regle dans la BC
Regle tete_Base(BC base);        //acceder a la regle se trouvant la tete de la base
