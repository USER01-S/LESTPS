#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "supprission.h"
//FONCTION POUR DONNEE LA MAIN EB UTILISATEUR DE SAISIR VOTRE DONNEES 
void saisir(Noeud* noeud) {
    printf("saisir le prix : ");
    scanf("%f", &noeud->prix);
    printf("saisir le prixht : ");
    scanf("%f", &noeud->prixth);
    printf("saisir la moyenne : ");
    scanf("%f", &noeud->moyenne);
    printf("saisir la quantite : ");
    scanf("%d", &noeud->quantite);
    printf("saisir le type : ");
    scanf("%s",noeud->type);
}
int main() {
    Noeud* tete = (Noeud*)malloc(sizeof(Noeud));
    saisir(tete);
    Noeud* noeud1 = creatnoeud(2, 342, 24, 3514, "2eme");
    tete->suivant = noeud1;
    Noeud* noeud2 = creatnoeud(3, 343, 25, 3515, "3eme");
    noeud1->suivant=noeud2;
    Noeud* noeud3=AjouterEnMilieu(tete,2,2333, 34233, 2444, 3514, "premier");
    afficher(tete);
    tete=modifierEnMilieu(tete,1,2333, 34233, 2444, 3514,"la modification");
    afficher(tete);
    Noeud* courant = tete;
    while (courant != NULL) {
        Noeud* suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }
}
