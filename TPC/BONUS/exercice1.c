#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Date {
    int jour ;
    int mois ; 
    int annee ; 
}Date;
typedef struct Etudiant {
   char nom[31];
   int identifiant;
   float note;
   Date datenaissance ;
   struct Etudiant* next ;
}Etudiant;
typedef struct{
   Etudiant* first ;
}Liste ;
typedef enum{
   Verte,
   Jaune,
   Rouge
}Couleur;
typedef struct ElementPile {
    Couleur couleur;
    Etudiant* etudiant ;
    struct ElementPile *precedent;
}ElementPile;
typedef struct Pile{
        ElementPile* sommet;
}Pile;
void saiser(Etudiant* E){
  printf("saisir le nom de Etudiant : ");
  scanf("%s",E->nom);
  printf("saisir ID d'etudiant :  ");
  scanf("%d",&(E->identifiant));
  printf("saisir la note d'etudiant : ");
  scanf("%f",&(E->note));
  printf("la date de naissence d'etudaint : \n");
  printf(" le jour : ");
  scanf("%d",&((E->datenaissance).jour));
  printf("le mois : ");
  scanf("%d",&((E->datenaissance).mois));
  printf("l'annee : ");
  scanf("%d",&((E->datenaissance).annee));
  E->next = NULL;
}
void ajouterEtudiant(Liste* l, Etudiant* E) {
    Etudiant* courant = l->first;
    Etudiant* precedent = NULL;
    while (courant != NULL && strcmp(E->nom, courant->nom) > 0) {
        precedent = courant;
        courant = courant->next;
    }
    if (precedent == NULL) {
        E->next = l->first;
        l->first = E;
    } else {
        precedent->next = E;
        E->next = courant;
    }
}
void afficher(Liste *l){
     Etudiant *courant = l->first;
    if (courant == NULL) {
        printf("La liste est vide.\n");
        return;
    }
    printf("\n--- Liste des Etudiants (Ordre Alphabetique) ---\n");
    while (courant != NULL) {
        printf("ID: %d | Nom: %-20s | Note: %.2f | Date: %02d/%02d/%d\n", 
                courant->identifiant, 
                courant->nom, 
                courant->note, 
                courant->datenaissance.jour, 
                courant->datenaissance.mois, 
                courant->datenaissance.annee);
        courant = courant->next;
    }
    printf("------------------------------------------------\n");
}
void creation(Liste* l, Pile *V, Pile* J, Pile* R) {
    if (l->first == NULL) {
        printf("La liste est vide.\n");
        return;
    }

    Etudiant* courant = l->first;

    while (courant != NULL) {
        // 1. ALLOCATION d'un nouvel élément pour chaque étudiant
        ElementPile* ele = malloc(sizeof(ElementPile));
        if (ele == NULL) exit(EXIT_FAILURE);

        ele->etudiant = courant;

        // 2. LOGIQUE DES COULEURS (selon l'énoncé)
        if (courant->note >= 10) {
            // MOYENNE -> VERT
            ele->couleur = Verte;
            ele->precedent = V->sommet;
            V->sommet = ele;
        } 
        else if (courant->note >= 5) {
            // ENTRE 5 ET 10 -> JAUNE
            ele->couleur = Jaune;
            ele->precedent = J->sommet;
            J->sommet = ele;
        } 
        else {
            // INFÉRIEUR A 5 -> ROUGE
            ele->couleur = Rouge;
            ele->precedent = R->sommet;
            R->sommet = ele;
        }

        // 3. PASSER A L'ETUDIANT SUIVANT DANS LA LISTE
        courant = courant->next;
    }
}
void afficherCouleur(Couleur c) {
    switch(c) {
        case Verte:
            printf("Couleur : VERTE\n");
            break;
        case Jaune:
            printf("Couleur : JAUNE\n");
            break;
        case Rouge:
            printf("Couleur : ROUGE\n");
            break;
        default:
            printf("Couleur inconnue\n");
    }
}
void afficherPile(Pile* p) {
    // 1. Vérifier si la pile existe et n'est pas vide
    if (p == NULL || p->sommet == NULL) {
        printf("La pile est vide.\n");
        return;
    }

    ElementPile *courant = p->sommet;
    
    // On affiche la couleur globale de cette pile une seule fois au début
    printf("\n--- Affichage de la Pile ---\n");
    afficherCouleur(courant->couleur); 
    while (courant != NULL) {
        if (courant->etudiant != NULL) {
            printf("ID: %d | Nom: %-20s | Note: %.2f | Date: %02d/%02d/%d\n", 
                    courant->etudiant->identifiant, 
                    courant->etudiant->nom, 
                    courant->etudiant->note, 
                    courant->etudiant->datenaissance.jour, 
                    courant->etudiant->datenaissance.mois, 
                    courant->etudiant->datenaissance.annee);
        }
        courant = courant->precedent; 
    }
    printf("---------------------------\n");
}
int main(){
   Pile *V=malloc(sizeof(Pile));
   Pile *R=malloc(sizeof(Pile));
   Pile *J=malloc(sizeof(Pile));
   Liste* l =malloc(sizeof(Liste));
   Etudiant* e =malloc(sizeof(Etudiant));
   Etudiant* r = malloc(sizeof(Etudiant));
   Etudiant* t = malloc(sizeof(Etudiant));
   saiser(e);
   saiser(r);
   saiser(t);
   ajouterEtudiant(l,e);
   ajouterEtudiant(l,r);
   ajouterEtudiant(l,t);
   afficher(l);
   creation ( l, V,  J, R);
   afficherPile(R);
   afficherPile(V);
   afficherPile(J);
   return 0;
}

