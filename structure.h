#ifndef STRUCTURE_H
#define STRUCTURE_H 

typedef struct{
    char pseudo[50]; 
    char classe[20];  // pour memoriser si il est 'guerrier','magicien'..
    char symbole[10]; // emoji du personnage 
    int armeActive; 
    int ligne; 
    int colonne;  
    int armeAntiqueTrouvee; // 0 = non trouvée, 1 = trouvée
    int tresorTrouve; // 0 = pas de trésor, 1 = trésor trouvé !
    int peutTeleporter; // 0 = normal, 1 = peut sauter n'importe où !
}Joueur; //fiche idd d un joueur  

typedef struct{
    char typeContenu[30] ; //'zombie', 'coffre'
    char symbole[10] ; // l emoji de la carte quand on la retourne 
    int estCachee ; // cahcer : 1 et visible : 0 
}Case ; 

#endif 



