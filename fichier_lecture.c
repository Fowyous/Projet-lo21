#include "main.h"
#include <string.h>
#include <stdlib.h>

BC *lecture_fichier(char *chemin){//lis les bases de connaissances dans le fichier et retourne la tête.
	FILE *file;
	char ligne[BUFFER];

        file = fopen(chemin, "r");

        if (file == NULL){
                printf("Ouverture du fichier impossible!!\n");
                exit(1);
        }
	//BC *bc_tete =  Creer_BC(NULL);
	//BC *bc_queue = bc_tete;
	BC *bc_tete = NULL;
	if (fgets(ligne, sizeof(ligne), file) != NULL){
		// le fichier ne dois pas contenir de \n
		ligne[strcspn(ligne, "\n")] = 0;
		// les bases sont séparées par , la variable bc_data contient toutes les infos necessaires pour remplire une base
		char *bc_data = strtok(ligne, ",");
		printf("bc_data : %s\n", bc_data);

		while (bc_data != NULL){
			//Créer une nouvelle base
			BC *nouvel_bc = Creer_BC(bc_tete);
			bc_tete = nouvel_bc;
			
			//Extraire le nom d'une base.
			char *bc_nom = strtok(bc_data, ";");
			nouvel_bc->nom = strdup(bc_nom);
			printf("bc_nom : %s\n", bc_nom);
			//Traitement de la régle dans la base
			char *regle_data = strtok(NULL, ",");
			printf("regle_data : %s\n", regle_data);
			while(regle_data != NULL){
				//Extraire une régle et la diviser en conclusion et proposition
				char *conclusion = strtok(regle_data, ":");
				printf("conclusion : %s\n", conclusion);//enl
				if (conclusion != NULL){		
					Regle* nouvel_regle = Creer_regle();
					Conclusion(nouvel_regle, conclusion);

					//Extraire les propositions
					char *propositions = strtok(NULL, ";");
					printf("propositions : %s\n", propositions);//enl
					if (propositions != NULL){	
						char *proposition = strtok(propositions, ":");
						while (proposition != NULL){
					printf("propositions : %s\n", propositions);//enl
							Ajout_proposition(nouvel_regle, proposition);
							proposition = strtok(NULL, ":");
						}
					}
				
					//Ajouter la régle a la base.
					Ajout_regle(nouvel_bc, nouvel_regle);
				}
				
				//Passer a la prochaine régle (si elle existe) dans la base
				regle_data = strtok(NULL, ";");
				printf("regle_data2 : %s\n", regle_data);
			}

			//Passer a la prochaine base
			bc_data = strtok(NULL, ",");

		}



/*
		int len = strlen(bc_data);
		bc_data[len] = ';';
		printf("bc_data : %s\n", bc_data);
		bc_data[len + 1] = '\0';
		printf("bc_data : %s\n", bc_data);
		
		char * mot = strtok(bc_data, ";");
		// le premier mot c'est le nom de la base
		if (mot) {
			Ajout_nom_BC(bc_queue, mot);
		}
		char* regle_data = strtok(NULL, ";");
		Regle *nouvel_regle = Creer_regle();// le premier mot c'est la conclusion
		while (regle_data){

			printf("regle_data : %s\n", regle_data);
			getchar();
			mot = strtok(regle_data, ":");
			if (mot) {
				Conclusion(nouvel_regle, mot);
			}	
			while (mot){//c'est la boucle pour les régles(condition a regler)
				mot = strtok(NULL, ":");
				printf("mot : %s\n", mot);
				getchar();
				if (mot){
					Ajout_proposition(nouvel_regle, mot);
				}
			}
			//regle_data = strtok(bc_data, regle_data);
			//printf("regle_data2 : %s\n", regle_data);
			regle_data = strtok(NULL, ";");
			
			printf("regle_data3 : %s\n", regle_data);
			getchar();

		}
		Ajout_regle(bc_queue, nouvel_regle);
		bc_queue = Creer_BC(bc_tete);*/
	}
	fclose(file);
	return bc_tete;
}

int main(){
	lecture_fichier("bases.txt");

}
