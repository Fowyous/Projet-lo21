#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>
#include <stdio.h>
#include <termios.h>

#define BUFFER 1025
//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//
//_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//structure//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\\
//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//

////////////////////////////////////structure proposition
typedef struct Propositions {
        char* proposition;
        struct Propositions* next;
}Propositions;

///////////////////////////////////structure regle
typedef struct Regle { 
        char* conclusion;
        Propositions* premisse;
	struct Regle* next;
}Regle;

///////////////////////////////////chaine de regles
typedef struct BC{
        char* nom;
        Regle* regle;
        struct BC* next;
}BC;

//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//
//_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//fonctions//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\\
//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//

Regle *Creer_regle();        //cree une regle vide
Regle *Regle_suivant(Regle *regle);//a regler!
void Ajout_proposition(Regle* regle, char* proposition);        //ajout une proposition a la premisse d une regle en queu
void Conclusion(Regle* regle, char* conclusion);        //cree la conclusion d une regle
bool est_dans_premisse(Propositions* premisse, char* ptest);        //Tester si une proposition appartient à la prémisse d’une règle, de manière récursive
Propositions supr_proposition(Propositions* premisse, char* proposition);        //il faut verif que la propo est dans la premisse
bool est_vide(Propositions* premisse);
char* tete_premisse(Propositions* premisse);        //revoie la tete de la premisse 
char* conclusion_regle(Regle *regle);        //renvoie la conclusion d une regle




BC* Creer_BC(BC* bases);        //cree une base vide a la queue d'une liste de bases si bases est NULL ca retourne une seule base
void Ajout_regle(BC *base, Regle* regle);        //ajout en queu la regle dans la BC
Regle* tete_Base(BC *base);        //acceder a la regle se trouvant la tete de la base

BC *bc_suivant(BC *base);//a regler!


BC *lecture_fichier(const char *chemin);
BC *sauvegarde(BC *base, const char *chemin);
void Ajout_nom_BC(BC* base, char* nom);

#endif
