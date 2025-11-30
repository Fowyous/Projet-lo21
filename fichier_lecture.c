#include "main.h"

BC *lecture_fichier(char *chemin){//lis les bases de connaissances dans le fichier et retourne la tête.
	FILE *file;
	char ligne[BUFFER];

        file = fopen(path, "r");

        if (file == NULL){
                printf("Ouverture du fichier impossible!!\n");
                exit(1);
        }
	BC *bc_tete =  Creer_BC();
	BC *bc_queue = bc_tete;
	if (fgets(ligne, sizeof(ligne, file)) != NULL){
		// le fichier ne dois pas contenir de \n
		ligne[strcspn(ligne, "\n")] = 0;

		// les bases sont séparées par , la variable bc_data contient toutes les infos necessaires pour remplire une base
		char *bc_data = strtok(ligne, ",");

		while (bc_data){
			char *mot = strtok(bc_data, ";");
			// le premier mot c'est le nom de la base
			if (mot) {
				bc_queue->nom = mot; //j'ai pas trouvé de fonction pour ca. a ajouter
			}
			regle_data = strtok(NULL, ";");
			while (regle_data){//c'est la boucle pour les régles(condition a regler)
				Regle *nouvel_regle = Creer_regle();
				mot = strtok(regle_data, ":");
				// le premier mot c'est la conclusion
				if (mot) {
					Conclusion(nouvel_regle, mot);
				}
				mot = strtok(NULL, ":");
				while (!strchr(mot, ';')){
					if (mot){
						Ajout_proposition(nouvel_regle, mot);
					}
				}
				Ajout_regle(bc_queue, nouvel_regle);
			}
			//il faut creer une fonction pour gerer ca
			bc_queue->next = Creer_BC();
			bc_queue->next = bc_queue;
		}
	}
	fclose(file);
	return bc_tete;
}
