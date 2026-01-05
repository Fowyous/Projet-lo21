#ifndef GESTION_BASE_H
#define GESTION_BASE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

BC *Creer_BC(BC* bases);          //Crée une base de connaissance et l'ajoute en queue et retourne la nouvelle base.
BC *bc_suivant(BC *base);          //Prend en parametre un pointeur vers une base, et retourne la base qui la suis.
char *nom_bc(BC *base);          //Prend en parametre une base, et retourne le nom de cette base sous forme de caractere.
void Ajout_regle(BC* base, Regle* regle);          //Prend en parametre un pointeur vers une base et un pointeur vers une regle et ajoute cette regle en queu de la liste de regles de la base, et ne retourne rien.
void Ajout_nom_BC(BC* base, char* nom);          //Prend en parametre un pointeur vers une base et une chaine de caractere "nom" et donne ce nom a la base, et ne retourne rien.
Regle* tete_Base(BC* base);          //Prend en parametre un pointeur vers une base, et retourne un pointeur vers la premiere regle de la liste de regle de la base.
void supr_Regle(BC *base);          //Prend en parametre un pointeur vers une base et supprime la regle en queu de la liste de regle de la base, et ne retourne rien.
BC *supr_bc(BC *base);          //Prend en parametre un pointeur vers une base et suprime toute les regles de la base et la base elle meme, et retourne un pointeur vers la base suivante.
int taille_base(BC *base);          //Prend en parametre un pointeur vers une base et calcule combien il y a de regle dans celle ci, et retourne l'entier "taille" de la base qui est sont nombre de regle.

#endif
