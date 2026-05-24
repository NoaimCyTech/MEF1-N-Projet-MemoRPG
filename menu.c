#include <stdio.h>
#include "structure.h"
#include "menu.h"

void afficherMenuAccueil() {
    printf("\n\033[35m **************************************** \033[0m\n");
    printf("\033[35m * BIENVENUE DANS LE MEMO-RPG      * \033[0m\n");
    printf("\033[35m **************************************** \033[0m\n\n");
}

// Fonction de sécurité pour éviter les crashs de scanf
void viderTampon() {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF);
}

int choisirArme() {
    int selection = 0;
    while(1) {
        printf("\n--- PREPARATION AU COMBAT ---\n");
        printf("1. Bouclier (vs Basilic)\n");
        printf("2. Torche   (vs Zombie)\n");
        printf("3. Hache    (vs Troll)\n");
        printf("4. Arc      (vs Harpie)\n");
        printf("=> Choisissez votre arme (1-4) : ");
        
        if (scanf("%d", &selection) != 1) {
            viderTampon();
        }

        if (selection >= 1 && selection <= 4) {
            break; // Saisie valide, on sort de la boucle
        }
        printf("ERREUR : Vous devez taper un chiffre entre 1 et 4.\n");
    }
    return selection;
}

int choisirAction() {
    int choixMenu = 0;
    while(1) {
        printf("\n--- ACTION DU TOUR ---\n");
        printf("1. Se déplacer dans le donjon\n");
        printf("2. Combattre\n");
        printf("3. Fuir (Quitter le jeu)\n");
        printf("=> Que voulez-vous faire ? (1-3) : ");
        
        if (scanf("%d", &choixMenu) != 1) {
            viderTampon();
        }

        if (choixMenu >= 1 && choixMenu <= 3) {
            break; // Saisie valide
        }
        printf("ERREUR : Option invalide. Entrez 1, 2 ou 3.\n");
    }
    return choixMenu;
}