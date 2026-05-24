#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"
#include "plateau.h"

void initialisation(Case grilleJeu[5][5]) {
    // Liste de tous les objets présents dans le donjon (25 éléments)
    char *listeElements[25] = {
        "basilic", "zombie", "troll", "harpie",
        "basilic", "zombie", "troll", "harpie",
        "tresor", "tresor",
        "epee_feu", "baton_controle", "grimoire", "dague_sommeil",
        "portail", "totem", "totem",
        "estvide", "estvide", "estvide", "estvide",
        "estvide", "estvide", "estvide", "estvide"
    };
    
    srand((unsigned int)time(NULL));
    
    // Mélange des éléments (Algorithme de Fisher-Yates)
    for (int idx = 24; idx > 0; idx--) {
        int r = rand() % (idx + 1);
        char *temp = listeElements[idx];
        listeElements[idx] = listeElements[r];
        listeElements[r] = temp;
    }

    // Remplissage de la grille 5x5
    int compteur = 0;
    for (int lig = 0; lig < 5; lig++) {
        for (int col = 0; col < 5; col++) {
            strcpy(grilleJeu[lig][col].typeContenu, listeElements[compteur]);
            grilleJeu[lig][col].estCachee = 1; // Toutes les cartes sont face cachée au départ
            compteur++;
        }
    }
}

void afficherPlateau(Case grilleJeu[5][5], Joueur jActuel) {
    printf("\n------ LE DONJON ------\n");
    
    // On agrandit le dessin de -1 à 5 pour inclure les bords de la carte (la base des joueurs)
    for(int lig = -1; lig <= 5; lig++) {
        for(int col = -1; col <= 5; col++) {
            
            // 1. Est-ce que le JOUEUR est sur ces coordonnées exactes ?
            if(jActuel.ligne == lig && jActuel.colonne == col) {
                printf("[%c]", jActuel.pseudo[0]); // Affiche la première lettre du pseudo
            } 
            
            // 2. Sinon, sommes-nous à l'intérieur du vrai labyrinthe (coordonnées 0 à 4) ?
            else if(lig >= 0 && lig <= 4 && col >= 0 && col <= 4) {
                
                // La case est-elle encore couverte par le brouillard ?
                if(grilleJeu[lig][col].estCachee == 1) {
                    printf("[?]"); 
                } 
                // Sinon, la case est révélée, on affiche son contenu
                else {
                    char* obj = grilleJeu[lig][col].typeContenu;
                    
                    if(strcmp(obj, "tresor") == 0) printf("[💰]");
                    else if(strcmp(obj, "zombie") == 0) printf("[🧟]");
                    else if(strcmp(obj, "basilic") == 0) printf("[🐉]");
                    else if(strcmp(obj, "troll") == 0) printf("[👹]");
                    else if(strcmp(obj, "harpie") == 0) printf("[🦅]");
                    else if(strcmp(obj, "epee_feu") == 0) printf("[⚔️]");
                    else if(strcmp(obj, "baton_controle") == 0) printf("[🦯]");
                    else if(strcmp(obj, "grimoire") == 0) printf("[📖]");
                    else if(strcmp(obj, "dague_sommeil") == 0) printf("[🗡️]");
                    else if(strcmp(obj, "portail") == 0) printf("[🌀]");
                    else if(strcmp(obj, "totem") == 0) printf("[🗿]");
                    else printf("[  ]"); // Case vide
                }
            } 
            
            // 3. Sinon, on est à l'extérieur du labyrinthe et il n'y a pas de joueur
            else {
                printf("   "); // On affiche 3 espaces pour s'aligner parfaitement avec les blocs du donjon
            }
        }
        printf("\n"); // Fin de la ligne, on passe à la suivante
    }
    printf("-----------------------\n");
}