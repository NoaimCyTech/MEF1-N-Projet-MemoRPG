#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "menu.h"
#include "structure.h"
#include "plateau.h"
#include "logique.h"
#include "score.h"

int main() {
    SetConsoleOutputCP(65001); // UTF-8 pour les emojis
    
    int nbParticipants = 0;

    do {
        printf("Combien d'aventuriers se lancent dans le donjon ? (2 a 4) : ");
        if (scanf("%d", &nbParticipants) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF); 
        }
        if(nbParticipants < 2 || nbParticipants > 4) {
            printf("Erreur : Il faut entre 2 et 4 joueurs.\n");
        }
    } while (nbParticipants < 2 || nbParticipants > 4);

    Joueur equipe[4];

    // Création des profils, attribution des classes et placement asymétrique
    for(int i = 0; i < nbParticipants; i++) {
        printf("\nJoueur %d, quel est votre pseudo ? : ", i + 1);
        scanf("%s", equipe[i].pseudo);
        
        equipe[i].armeAntiqueTrouvee = 0;
        equipe[i].tresorTrouve = 0;
        equipe[i].peutTeleporter = 0;

        switch(i) {
            case 0: 
                strcpy(equipe[i].classe, "Guerrier");
                equipe[i].ligne = -1; equipe[i].colonne = 3; 
                break; // Nord (décalé à droite)
            case 1: 
                strcpy(equipe[i].classe, "Ranger");
                equipe[i].ligne = 1;  equipe[i].colonne = -1; 
                break; // Ouest (décalé en haut)
            case 2: 
                strcpy(equipe[i].classe, "Magicien");
                equipe[i].ligne = 5;  equipe[i].colonne = 1; 
                break; // Sud (décalé à gauche)
            case 3: 
                strcpy(equipe[i].classe, "Voleur");
                equipe[i].ligne = 3;  equipe[i].colonne = 5; 
                break; // Est (décalé en bas)
        }
    }

    printf("\n--- L'EQUIPE EST PRETE ! LA QUETE DEMARRE ! ---\n");
    printf("\n🛡️ RAPPEL DES MISSIONS :\n");
    for(int i = 0; i < nbParticipants; i++) {
        if(i == 0) printf("- %s (Guerrier) doit trouver l'Epee de feu [⚔️]\n", equipe[i].pseudo);
        if(i == 1) printf("- %s (Ranger) doit trouver le Baton de controle [🦯]\n", equipe[i].pseudo);
        if(i == 2) printf("- %s (Magicien) doit trouver le Grimoire [📖]\n", equipe[i].pseudo);
        if(i == 3) printf("- %s (Voleur) doit trouver la Dague de sommeil [🗡️]\n", equipe[i].pseudo);
    }
    printf("N'oubliez pas : il vous faut absolument un Tresor [💰] et votre Arme Antique pour gagner !\n\n");
    
    Case carteDonjon[5][5];
    initialisation(carteDonjon);
    afficherMenuAccueil();

    int partieEnCours = 1;
    int indexJoueur = 0;

    while (partieEnCours == 1) {
        int tourTermine = 0;
        printf("\n========================================\n");
        printf("     C'EST AU TOUR DE : %s (%s)\n", equipe[indexJoueur].pseudo, equipe[indexJoueur].classe);
        printf("========================================\n");

        equipe[indexJoueur].armeActive = choisirArme();
        afficherPlateau(carteDonjon, equipe[indexJoueur]);

        int direction = 0;
        int vientDeSeTeleporter = 0;

        if (equipe[indexJoueur].peutTeleporter == 1) {
            printf("\n🌀 PORTAIL ACTIF : Ou veux-tu te teleporter ? (Cases cachees)\n");
            printf("Ligne (0-4) : "); scanf("%d", &equipe[indexJoueur].ligne);
            printf("Colonne (0-4) : "); scanf("%d", &equipe[indexJoueur].colonne);
            equipe[indexJoueur].peutTeleporter = 0;
            vientDeSeTeleporter = 1;
        } 
        
        if (vientDeSeTeleporter == 0) {
            // Entrée automatique depuis les bases extérieures
            if (equipe[indexJoueur].ligne == -1) direction = 2; 
            else if (equipe[indexJoueur].ligne == 5) direction = 1;  
            else if (equipe[indexJoueur].colonne == -1) direction = 4; 
            else if (equipe[indexJoueur].colonne == 5) direction = 3;  
            else {
                printf("\n--- OU VEUX-TU ALLER ? ---\n");
                printf("1: Haut ^ | 2: Bas v | 3: Gauche < | 4: Droite >\n");
                printf("Ton choix : ");
                scanf("%d", &direction);
            }

            switch(direction) {
                case 1: if(equipe[indexJoueur].ligne > 0 || equipe[indexJoueur].ligne == 5) equipe[indexJoueur].ligne--; else printf("🔴 Mur au Nord.\n"); break;
                case 2: if(equipe[indexJoueur].ligne < 4 || equipe[indexJoueur].ligne == -1) equipe[indexJoueur].ligne++; else printf("🔴 Mur au Sud.\n"); break;
                case 3: if(equipe[indexJoueur].colonne > 0 || equipe[indexJoueur].colonne == 5) equipe[indexJoueur].colonne--; else printf("🔴 Mur a l'Ouest.\n"); break;
                case 4: if(equipe[indexJoueur].colonne < 4 || equipe[indexJoueur].colonne == -1) equipe[indexJoueur].colonne++; else printf("🔴 Mur a l'Est.\n"); break;
                default: printf("Direction invalide.\n"); break;
            }
        }

        if (equipe[indexJoueur].ligne >= 0 && equipe[indexJoueur].ligne <= 4 && 
            equipe[indexJoueur].colonne >= 0 && equipe[indexJoueur].colonne <= 4) {
            
            Case *caseActuelle = &carteDonjon[equipe[indexJoueur].ligne][equipe[indexJoueur].colonne];
            caseActuelle->estCachee = 0;
            afficherPlateau(carteDonjon, equipe[indexJoueur]);

            char* objetTrouve = caseActuelle->typeContenu;

            if (strcmp(objetTrouve, "basilic") == 0 || strcmp(objetTrouve, "zombie") == 0 || 
                strcmp(objetTrouve, "troll") == 0 || strcmp(objetTrouve, "harpie") == 0) {
                
                printf("😱 OH NON ! Un %s sauvage se cache ici !\n", objetTrouve);
                if (resoudreCombat(objetTrouve, equipe[indexJoueur].armeActive)) {
                    printf("⚔️ BRAVO ! Tu as utilise la bonne arme.\n");
                    strcpy(caseActuelle->typeContenu, "estvide");
                } else {
                    printf("☠️ AIE ! Ton arme est inefficace. Tu es vaincu...\n");
                    
                    switch(indexJoueur) {
                        case 0: equipe[indexJoueur].ligne = -1; equipe[indexJoueur].colonne = 3; break;
                        case 1: equipe[indexJoueur].ligne = 1;  equipe[indexJoueur].colonne = -1; break;
                        case 2: equipe[indexJoueur].ligne = 5;  equipe[indexJoueur].colonne = 1; break;
                        case 3: equipe[indexJoueur].ligne = 3;  equipe[indexJoueur].colonne = 5; break;
                    }
                    
                    printf("🌫️ Le brouillard magique recouvre le labyrinthe...\n");
                    for(int l = 0; l < 5; l++) {
                        for(int c = 0; c < 5; c++) {
                            carteDonjon[l][c].estCachee = 1;
                        }
                    }
                    tourTermine = 1;
                }
            } 
            else if (strcmp(objetTrouve, "tresor") == 0) {
                printf("💰 INCROYABLE ! %s (%s) a trouve le coffre au tresor !\n", equipe[indexJoueur].pseudo, equipe[indexJoueur].classe);
                equipe[indexJoueur].tresorTrouve = 1;
                if (equipe[indexJoueur].armeAntiqueTrouvee == 1) {
                    printf("🏆 VICTOIRE ! %s (%s) possede son arme ET le tresor.\n", equipe[indexJoueur].pseudo, equipe[indexJoueur].classe);
                    partieEnCours = 0;
                } else {
                    printf("Il ne te manque plus que ton arme antique pour gagner !\n");
                }
            } 
            else if (strcmp(objetTrouve, "epee_feu") == 0 || strcmp(objetTrouve, "baton_controle") == 0 || 
                     strcmp(objetTrouve, "grimoire") == 0 || strcmp(objetTrouve, "dague_sommeil") == 0) {
                char armeRequise[20];
                if (indexJoueur == 0) strcpy(armeRequise, "epee_feu");
                else if (indexJoueur == 1) strcpy(armeRequise, "baton_controle");
                else if (indexJoueur == 2) strcpy(armeRequise, "grimoire");
                else strcpy(armeRequise, "dague_sommeil");

                if (strcmp(objetTrouve, armeRequise) == 0) {
                    printf("✨ MAGNIFIQUE ! %s (%s) a trouve SON arme antique : %s !\n", equipe[indexJoueur].pseudo, equipe[indexJoueur].classe, armeRequise);
                    equipe[indexJoueur].armeAntiqueTrouvee = 1;
                    if (equipe[indexJoueur].tresorTrouve == 1) {
                        printf("🏆 VICTOIRE TOTALE ! %s (%s) possede son arme ET un tresor.\n", equipe[indexJoueur].pseudo, equipe[indexJoueur].classe);
                        partieEnCours = 0;
                    } else {
                        printf("Il ne te manque plus qu'un tresor pour gagner !\n");
                    }
                } else {
                    printf("Dommage, c'est l'arme antique d'un autre aventurier. Tu passes ton chemin...\n");
                }
            } 
            else if (strcmp(objetTrouve, "portail") == 0) {
                printf("🌀 PORTAIL MAGIQUE ! %s (%s) peut se teleporter n'importe ou au prochain tour !\n", equipe[indexJoueur].pseudo, equipe[indexJoueur].classe);
                equipe[indexJoueur].peutTeleporter = 1;
            } 
            else if (strcmp(objetTrouve, "totem") == 0) {
                executerTotem(carteDonjon, equipe, indexJoueur);
                tourTermine = 1;
            } 
            else {
                printf("😌 Ouf, la voie est libre.\n");
            }
        }

        if (partieEnCours == 1 && tourTermine == 1) {
            indexJoueur++;
            if(indexJoueur >= nbParticipants) indexJoueur = 0;
        }
    }

    printf("\n--- TOUTES LES CARTES SONT REVELEES ! ---\n");
    for(int l = 0; l < 5; l++) {
        for(int c = 0; c < 5; c++) {
            carteDonjon[l][c].estCachee = 0;
        }
    }
    
    Joueur joueurFantome;
    joueurFantome.ligne = -10; joueurFantome.colonne = -10;
    afficherPlateau(carteDonjon, joueurFantome);
    
    printf("\n🏆 Bravo a %s (%s) ! --- FIN DE LA PARTIE ---\n", equipe[indexJoueur].pseudo, equipe[indexJoueur].classe);
    sauvegarderScores(equipe, nbParticipants, equipe[indexJoueur].pseudo);
    
    return 0;
}