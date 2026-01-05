#include "fichier_lecture.h"

BC *Sauvegarde(BC *base, const char *chemin){
	FILE *file;
	file = fopen(chemin, "w");
	if (file == NULL){
		printf("Ouverture du fichier impossible!!\n");
		exit(EXIT_FAILURE);
	}
	while (base){
		fprintf(file, "BC: %s\n", nom_bc(base));
		Regle *regle;
		do {
			regle = tete_Base(base);
			if (conclusion_regle(regle) != NULL){
				fprintf(file, "REGL: %s\n", conclusion_regle(regle));
			}
			else 
				break;
			while (tete_premisse(regle) != NULL){
				fprintf(file, "    PROPOS: %s\n", tete_premisse(regle));
				supr_proposition(regle);
			}
			supr_Regle(base);
		}while (regle);
		base = supr_bc(base);
	}
	fclose(file);

}
BC *lecture_fichier(const char *chemin){//lis les bases de connaissances dans le fichier et retourne la tête.
	FILE *file;
	char ligne[BUFFER];

        file = fopen(chemin, "r");

        if (file == NULL){
                printf("Ouverture du fichier impossible!!\n");
                exit(EXIT_FAILURE);
        }
	
	BC *tete_base = NULL;
	BC *base = tete_base;
	Regle * nouvel_regle;
	while (fgets(ligne, sizeof(ligne), file) != NULL){
		if (strncmp(ligne, "BC:", 3) == 0) {//ligne contiendera seulement le nom de la base
			if (tete_base == NULL){
				base = Creer_BC(NULL);
				tete_base = base;
			}
			else
			base = Creer_BC(tete_base);

			char * nom_base = strdup(ligne + 4);// on enleve BC: du nom
			nom_base[strlen(nom_base) - 1] = '\0';//on enleve le \n
			Ajout_nom_BC(base, nom_base);
		}
		else if (strncmp(ligne, "REGL:", 5) == 0){
		
			nouvel_regle = Creer_regle(NULL);
			char * conclusion = strdup(ligne + 6);// on enleve REGL:
			conclusion[strlen(conclusion) - 1] = '\0';//on enleve le \n
			Conclusion(nouvel_regle, conclusion);
			Ajout_regle(base, nouvel_regle);
		}
		else if (strncmp(ligne, "    PROPOS:", 11) == 0){
			char *proposition = strdup(ligne + 12);// on enleve le 	PROPOS:
			proposition[strlen(proposition) - 1] = '\0';//on enleve le \n
			Ajout_proposition(nouvel_regle, proposition);
		}
	
	}

	fclose(file);
	return tete_base;
}

