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

///////////////////////////////////structure de la liste de fait
typedef struct liste_faits {
    char* fait;
    int nombre_apparition;
    struct liste_faits* next;
} Liste_faits;

///////////////////////////////////structure de la base de connaissance
typedef struct BC{
        char* nom;
        Regle* regle;
        Liste_faits* faits;
        struct BC* next;
}BC;


//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//
//_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//fonctions//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\\
//¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_/¯\_//

Regle *Creer_regle();        //cree une regle vide
Regle *Regle_suivant(Regle *regle); // je ne suis pas sûr de l'utilité de cette fonction et je ne l'ai pas testé
void Ajout_proposition(Regle* regle, char* proposition);        //ajout une proposition a la premisse d une regle en queu
void Conclusion(Regle* regle, char* conclusion);        //cree la conclusion d une regle
bool est_dans_premisse(Propositions* premisse, char* ptest);        //Tester si une proposition appartient à la prémisse d’une règle, de manière récursive
//Propositions supr_proposition(Propositions* premisse, char* proposition);        //il faut verif que la propo est dans la premisse
void supr_proposition(Regle *regle);//supprime la proposition en tete d'une regle
bool est_vide(Propositions* premisse);
char* tete_premisse(Regle *regle);        //revoie la tete de la premisse 
char* conclusion_regle(Regle *regle);        //renvoie la conclusion d une regle




BC* Creer_BC(BC* bases);        //cree une base vide a la queue d'une liste de bases si bases est NULL ca retourne une seule base
void Ajout_regle(BC *base, Regle* regle);        //ajout en queu la regle dans la BC
Regle* tete_Base(BC *base);        //acceder a la regle se trouvant la tete de la base
void supr_Regle(BC *base);
BC *supr_bc(BC *base);//supprime la base en tete et renvoie la base suivante
void Ajout_nom_BC(BC* base, char* nom);
BC *bc_suivant(BC *base);
char *nom_bc(BC *base);

BC *lecture_fichier(const char *chemin);
BC *Sauvegarde(BC *base, const char *chemin);// ca efface aussi la base.

#endif
