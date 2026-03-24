#include<stdio.h>
#include <stdlib.h>
typedef struct Liste {
      int note ;
      struct Liste* suivant ;
      }Liste;
Liste* creaListe(int note) {
    Liste* nextListe = (Liste*)malloc(sizeof(Liste));
    if (nextListe == NULL) 
        return NULL;
    nextListe->note = note; 
    nextListe->suivant = NULL;
    return nextListe;
}
Liste* insererEnd(Liste* p, int note){
     Liste* newListe = creaListe(note);
     Liste* courant = p ;
     if(p==NULL){
        printf("la liste est vide");
        return NULL ;
        }
     if(p->suivant==NULL){
         p->suivant=newListe;
         return p ;
         }
     while(courant->suivant!=NULL)
           courant=courant->suivant;
     courant->suivant=newListe;
     return p ;
     }
Liste* trier(Liste* p){
    Liste* debut ;
    Liste* next ;
    for(debut = p ;  p->suivant!=NULL; debut=debut->suivant){
        for(next = p->suivant ;  p->suivant !=NULL; next = next->suivant){
            if(debut->note > next->note){
                int b ; 
                b = debut->note;
                debut->note=next->note;
                next->note = b ;
                }
              }
           }
   return p ;
}
void afficher(Liste* tete) {
    int i = 1 ;
    Liste* Courant = tete;
    while (Courant != NULL) {
        printf("\n--- NOTE %d ---\n",i);
        printf("note : %d \n", Courant->note);
        Courant = Courant->suivant;
        i++;
    }
    printf("NULL\n");
}
int main() {
   Liste* p = creaListe(3);
   p =insererEnd(p, 4);
   p =insererEnd(p, -7);
   p =insererEnd(p, 2);
   p =insererEnd(p, -2);
   p =insererEnd(p, 10);
   p =insererEnd(p, -4);
   p =insererEnd(p, 0);
   p =insererEnd(p, -2);
   p =insererEnd(p, 46);
   afficher(p);
   p=trier(p);
   afficher(p);
}
