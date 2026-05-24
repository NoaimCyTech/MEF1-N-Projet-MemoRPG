#include <stdio.h>
#include <string.h>
#include "score.h"
#include "structure.h"


typedef struct{
    char pseudo[50]; 
    int parties; 
    int victoires ;
}Historique; 

void sauvegarderScores(Joueur equipe[], int nbMembres, char nomGagnant[]) {
    Historique baseDeDonnees[100];
    int totalEnregistres = 0;
    
    // 1. Lecture et sécurisation (max 100 lignes)
    FILE *fichierLect = fopen("score.txt", "r");
    if (fichierLect != NULL) {
        while (totalEnregistres < 100 && fscanf(fichierLect, "%s %d %d", 
               baseDeDonnees[totalEnregistres].pseudo, 
               &baseDeDonnees[totalEnregistres].parties, 
               &baseDeDonnees[totalEnregistres].victoires) == 3) {
            totalEnregistres++;
        }
        fclose(fichierLect);
    }

    // 2. Traitement des joueurs de la partie actuelle
    for (int p = 0; p < nbMembres; p++) {
        int index = -1;
        
        // Cherche si le joueur existe déjà
        for (int j = 0; j < totalEnregistres; j++) {
            if (strcmp(equipe[p].pseudo, baseDeDonnees[j].pseudo) == 0) {
                index = j;
                break;
            }
        }

        // Mise à jour ou Création
        if (index != -1) {
            baseDeDonnees[index].parties++;
            if (strcmp(equipe[p].pseudo, nomGagnant) == 0) {
                baseDeDonnees[index].victoires++;
            }
        } else if (totalEnregistres < 100) {
            strcpy(baseDeDonnees[totalEnregistres].pseudo, equipe[p].pseudo);
            baseDeDonnees[totalEnregistres].parties = 1;
            baseDeDonnees[totalEnregistres].victoires = (strcmp(equipe[p].pseudo, nomGagnant) == 0) ? 1 : 0;
            totalEnregistres++;
        }
    }

    // 3. Ecriture de la sauvegarde propre
    FILE *fichierEcr = fopen("score.txt", "w");
    if (fichierEcr != NULL) {
        for (int i = 0; i < totalEnregistres; i++) {
            fprintf(fichierEcr, "%s %d %d\n", baseDeDonnees[i].pseudo, baseDeDonnees[i].parties, baseDeDonnees[i].victoires);
        }
        fclose(fichierEcr);
        printf("\n[Succes] L'historique du donjon a ete mis a jour.\n");
    } else {
        printf("\n[Erreur] Impossible d'ecrire la sauvegarde.\n");
    }
}