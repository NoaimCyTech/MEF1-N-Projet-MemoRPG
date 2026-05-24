#include <stdio.h>
#include <string.h>
#include "logique.h"
#include "structure.h"

int resoudreCombat(char monstre[], int armeChoisie) {
    // Logique simplifiée : on vérifie directement la combinaison gagnante
    int victoire = 0;
    
    if (strcmp(monstre, "basilic") == 0 && armeChoisie == 1) victoire = 1;
    else if (strcmp(monstre, "zombie") == 0 && armeChoisie == 2) victoire = 1;
    else if (strcmp(monstre, "troll") == 0 && armeChoisie == 3) victoire = 1;
    else if (strcmp(monstre, "harpie") == 0 && armeChoisie == 4) victoire = 1;
    
    return victoire;
}

void executerTotem(Case grille[5][5], Joueur heros[], int tourActuel) {
    int ligneCible, colCible;
    printf("\n🗿 TOTEM DE TRANSMUTATION ! Fin de ton tour.\n");

    // Boucle sécurisée avec gestion des limites de la grille
    while (1) {
        printf("Ligne (0-4) : ");
        scanf("%d", &ligneCible);
        printf("Colonne (0-4) : ");
        scanf("%d", &colCible);

        if (ligneCible >= 0 && ligneCible <= 4 && colCible >= 0 && colCible <= 4) {
            if (grille[ligneCible][colCible].estCachee == 1) {
                break; // Coordonnées valides et case cachée, on sort de la boucle
            } else {
                printf("⚠️ Erreur : Case deja revelee.\n");
            }
        } else {
            printf("⚠️ Erreur : Coordonnees hors du donjon.\n");
        }
    }

    // Échange des cases
    int lActuelle = heros[tourActuel].ligne;
    int cActuelle = heros[tourActuel].colonne;
    
    Case memoire = grille[lActuelle][cActuelle];
    grille[lActuelle][cActuelle] = grille[ligneCible][colCible];
    grille[ligneCible][colCible] = memoire;

    printf("✨ Transmutation reussie !\n");

    // Retour à la base après utilisation du Totem
    switch(tourActuel) {
        case 0: heros[tourActuel].ligne = -1; heros[tourActuel].colonne = 3; break;
        case 1: heros[tourActuel].ligne = 1;  heros[tourActuel].colonne = -1; break;
        case 2: heros[tourActuel].ligne = 5;  heros[tourActuel].colonne = 1; break;
        case 3: heros[tourActuel].ligne = 3;  heros[tourActuel].colonne = 5; break;
    }

    // On recache le plateau (correction du bug de la ligne 1)
    for(int l = 0; l < 5; l++) {
        for(int c = 0; c < 5; c++) {
            grille[l][c].estCachee = 1;
        }
    }
}