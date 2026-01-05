#ifndef GESTION_LISTE_H
#define GESTION_LISTE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

bool est_dans_liste_faits(Liste_faits* liste, char* fait_test);          //Prend en parametre un pointeur vers une liste de faits et une chaine de caractere "fait_test", et retourne vrai si le fait est dans la liste.
void Ajout_fait(Liste_faits* liste, char* nouveau_fait);          //Prend en parametre un pointeur vers une liste de faits et une chaine de caractere "nouveau_fait", ajoute ce fait ou incremente son nombre d'apparition, et ne retourne rien.
void afficher_liste_faits(Liste_faits* liste);          //Prend en parametre un pointeur vers une liste de faits et affiche chaque fait dans le terminal, et ne retourne rien.
void supprimer_fait(Liste_faits** liste, char* fait_a_supprimer);          //Prend en parametre un pointeur vers une liste de faits et une chaine "fait_a_supprimer", supprime ou decremente ce fait, et ne retourne rien.
bool est_videliste(Liste_faits* liste);          //Prend en parametre un pointeur vers une liste de faits et retourne vrai si la liste est vide.
int taille_faits(Liste_faits* liste);          //Prend en parametre un pointeur vers une liste de faits et retourne le nombre de faits dans celle-ci.

#endif
