#include<stdio.h>
#include <stdlib.h>
typedef struct Liste {
      struct Note* suivant ;
      }Liste;
typedef struct Note {
      int note ;
      struct Note* suivant ;
      }Note;
Liste* AjouterAdebut(Liste* tete, int note){
      Note* Nouvnote =(Note*)malloc(sizeof(Note));
      Nouvnote->note=note;
      Nouvnote->suivant = NULL;
      if(tete!=NULL){
         tete->suivant = Nouvnote;
         return tete;
       }      
}
Liste* creaListe(int note) {
    Liste* liste = (Liste*)malloc(sizeof(Liste));
    Note* notes = (Note*)malloc(sizeof(Note));
    if (liste == NULL) 
        return NULL;
    notes->note = note; 
    notes->suivant = NULL;
    liste->suivant=notes;
    return liste;
}
Liste* insererEnd(Liste* p, int note){
     Note* Nouvnote =(Note*)malloc(sizeof(Note));
     Nouvnote->note=note;
     Nouvnote->suivant = NULL;
     Note* courant = p->suivant ;
     if(p==NULL){
        printf("la liste est vide");
        return NULL ;
        }
     if(p->suivant==NULL){
         p->suivant=Nouvnote;
         return p ;
         }
     while(courant->suivant!=NULL)
          courant=courant->suivant;
     courant->suivant=Nouvnote;
     return p ;
     }
void afficher(Liste* tete) {
    int i = 1 ;
    if (tete == NULL || tete->suivant == NULL) {
        printf("La liste est vide.\n");
        return;
    }
    Note* Courant = tete->suivant;
    while (Courant != NULL) {
        printf("%d --> ", Courant->note);
        Courant = Courant->suivant;
        i++;
    }
    printf("NULL\n");
}
Liste* trier(Liste* p) {
    if (p == NULL) 
       return NULL;
    Note *i, *j;
    int temp;
    for (i = p->suivant; i->suivant != NULL; i = i->suivant) {
        for (j = i->suivant; j != NULL; j = j->suivant) {
            if (i->note > j->note) {
                temp = i->note;
                i->note = j->note;
                j->note = temp;
            }
        }
    }
    return p;
}
void Separer(Liste* p, Liste* listepositive ,Liste* listenegative){ 
    Note* courant = p->suivant ;
    if (p == NULL || p->suivant == NULL) {
        printf("La liste est vide.\n");
        return;
    }
    while(courant!=NULL){
       if(courant->note <= 0 ){
          listenegative=insererEnd(listenegative, courant->note);
          listepositive->suivant=courant->suivant;
          }/*else{
          listepositive=insererEnd(listepositive, courant->note);
          
          }*/
          courant=courant->suivant;
}
}

int main() {
   Liste *listepositive = (Liste*)malloc(sizeof(Liste));
   Liste *listenegative = (Liste*)malloc(sizeof(Liste));
   listepositive->suivant=NULL;
   listenegative->suivant=NULL;
   Liste* p = creaListe(3);
   p =insererEnd(p, 4);
   p =insererEnd(p, -7);
   p =insererEnd(p, 2);
   //p =insererEnd(p, -2);
   p =insererEnd(p, 10);
   p =insererEnd(p, -4);
  // p =insererEnd(p, 0);
   p =insererEnd(p, -2);
   p =insererEnd(p, 46);
   afficher(p);
   printf("\n");
   p=trier(p);
   printf("apres le trei\n");
   printf("\n");
   afficher(p);
   printf("\n");
   Separer(p,listepositive,listenegative);
   afficher(listepositive);
   printf("\n");
   afficher(listenegative);
   return 0 ;
}
