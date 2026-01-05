#ifndef GESTION_REGLE_H
#define GESTION_REGLE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

Regle* Creer_regle();          //Prend aucun parametre, et retourne une regle vide.
void Conclusion(Regle* regle, char* conclusion);          //Prend en parametre un pointeur vers une regle et une chaine de caratere conclusion et fait que la conclusion de la regle soit la conclusion donne, et ne retourne rien.
bool est_vide(Propositions* premisse);          //Prend en parametre un pointeur vers une premisse et regarde si elle est vide ou non, et retourne un boolein VRAI ou FAUX.
Regle *Regle_suivant(Regle *regle);          //Prend en parametre un pointeur vers une regle, et retourne un pointeur vers la regle suivante.
void Ajout_proposition(Regle* regle, char* proposition);          //Prend en parametre un ponteur vers une regle et une chaine de caractere "proposition" et ajoute "proposition" en queu de la premisse, et ne retourne rien.
char* conclusion_regle(Regle *regle);          //Prend en parametre un ponteur vers une regle, et retourne la chaine de caractere contenant la conclusion de la regle si elle existe ou null sinon.
char* tete_premisse(Regle *regle);          //Prend en parametre un ponteur vers une regle, et retourne un pointeur vers la tete de la premisse si elle existe sinon null.
bool est_dans_premisse(Propositions* premisse, char* ptest);          //Prend en parametre un ponteur vers une premisse et une chaine de caractere "ptest" regarde si "ptest est dans premisse, et retourne un boolein VRAI si oui et FAUX si non.
void supr_proposition(Regle *regle);          //Prend en parametre un ponteur vers une regle et supprime la propositionen tete de la premisse, et retourne rien.
void afficher_regle(Regle *regle);          //Prend en parametre un ponteur vers une regle et affiche conclusion et premisse de la regle, et retourne rien.
Propositions* proposition_suivante(Propositions* propo);          //Prend en parametre un pointeur vers la tete d'un liste de proposition, et retourne le suivant de cette liste.
void suprimer_proposition(Regle *regle, char *propo);          //prend  en parametre un pointeur vers une regle et une chaine de caractere propo, et suprime la proposition propo dans la regle

#endif
