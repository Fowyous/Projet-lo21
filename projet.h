#include <stdbool.h>

typedef struct Premisse {
        char* proposition;
        struct Premisse* next;
}Premisse;

typedef struct { 
        char* conclusion;
        Premisse premisse;
}Regle;

typedef struct { 
        Regle regle;
        struct BC* next;
}BC;


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
