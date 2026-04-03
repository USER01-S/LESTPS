#include <stdio.h>
#include <stdlib.h>

/* ============================================================
   STRUCTURE
   ============================================================ */
typedef struct Noeud {
    int valeur;
    struct Noeud *suivant;
    struct Noeud *precedent;
} Noeud;

/* ============================================================
   CREATION D'UN NOEUD
   ============================================================ */
Noeud* creerNoeud(int valeur) {
    Noeud *n = (Noeud*)malloc(sizeof(Noeud));
    if (!n) { fprintf(stderr, "Erreur malloc\n"); exit(EXIT_FAILURE); }
    n->valeur    = valeur;
    n->suivant   = n;
    n->precedent = n;
    return n;
}

/* ============================================================
   INSERTION EN FIN DE LISTE
   ============================================================ */
void insererFin(Noeud **tete, int valeur) {
    Noeud *nouveau = creerNoeud(valeur);
    if (*tete == NULL) {
        *tete = nouveau;
        return;
    }
    Noeud *dernier   = (*tete)->precedent;
    dernier->suivant  = nouveau;
    nouveau->precedent = dernier;
    nouveau->suivant   = *tete;
    (*tete)->precedent = nouveau;
}

/* ============================================================
   AFFICHAGE DE LA LISTE (un seul tour)
   ============================================================ */
void afficherListe(Noeud *tete) {
    if (tete == NULL) { printf("Liste vide.\n"); return; }
    Noeud *courant = tete;
    printf("↔ ");
    do {
        printf("[%d] ↔ ", courant->valeur);
        courant = courant->suivant;
    } while (courant != tete);
    printf("(retour tête)\n");
}

/* ============================================================
   VALEUR A UNE POSITION DONNEE (base 0)
   ============================================================ */
int valeurPosition(Noeud *tete, int position) {
    if (tete == NULL || position < 0) {
        printf("Position invalide ou liste vide.\n");
        return -1;
    }

    Noeud *courant = tete;

    for (int i = 0; i < position; i++) {
        courant = courant->suivant;
        if (courant == tete) {
            printf("Position %d hors de la liste.\n", position);
            return -1;
        }
    }

    return courant->valeur;
}

/* ============================================================
   LIBERATION MEMOIRE
   ============================================================ */
void libererListe(Noeud *tete) {
    if (tete == NULL) return;
    Noeud *courant = tete->suivant;
    while (courant != tete) {
        Noeud *tmp = courant->suivant;
        free(courant);
        courant = tmp;
    }
    free(tete);
}

/* ============================================================
   MAIN
   ============================================================ */
int main() {
    Noeud *liste = NULL;

    insererFin(&liste, 10);
    insererFin(&liste, 20);
    insererFin(&liste, 30);
    insererFin(&liste, 40);
    insererFin(&liste, 50);

    printf("Liste : ");
    afficherListe(liste);

    int pos;
    printf("Quelle position voulez-vous consulter ? (base 0) : ");
    scanf("%d", &pos);

    int val = valeurPosition(liste, pos);
    if (val != -1)
        printf("Valeur a la position %d : %d\n", pos, val);
    libererListe(liste);
    return 0;
}
