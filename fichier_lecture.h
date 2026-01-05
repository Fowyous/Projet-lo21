#ifndef FICHIER_LECTURE_H
#define FICHIER_LECTURE_H

#include "main.h"
#include <string.h>
#include <stdlib.h>

BC *Sauvegarde(BC *base, const char *chemin);          //souvegarde la liste des bases dans un fichier .txt a l'emplacement chemin
BC *lecture_fichier(const char *chemin);          //lis les bases de connaissances dans le fichier et retourne la tête.
