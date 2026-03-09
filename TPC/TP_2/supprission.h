#include "ajouter.h"
//supprission en debut de liste chaine 
Noeud* supprimerEnDebut(Noeud* tete ){
      if(tete==NULL){
        printf("la liste est vide ");
        return NULL;
        }
      Noeud* temp=tete;
      tete=tete->suivant;
      free(temp);
      return tete ;
}



//supprission en fin de liste chaine 
Noeud* supprimerEnFin(Noeud* tete ){
      if(tete==NULL){
        printf("la liste est vide ");
        return NULL;
        }
      Noeud* Courant=tete;
      if(tete->suivant==NULL){
        free(tete);
        return NULL;
        }
      while(Courant->suivant->suivant!=NULL)
      Courant=Courant->suivant;
      free(Courant->suivant);
      Courant->suivant=NULL;
      return tete;
     }
     
     
     
//supprission en milieu de liste chaine 
Noeud* supprimerEnMilieu(Noeud* tete, int post ){
      if(tete==NULL){
        printf("la liste est vide ");
        return NULL;
        }
      Noeud* temp=tete;
      int taille = tailleNoeud(tete);
      if(post<1 || post>taille){
         printf("la position invalide ");
         return tete ;
        }
      if(post==1){
         tete=tete->suivant;
         free(temp);
         return tete ;
      }
      Noeud* Courant = tete ;
      for(int i =1 ; i<post-1 ; i++)
          Courant=Courant->suivant;
      temp=Courant->suivant;
      Courant->suivant=temp->suivant;
      free(temp);
      return tete;
     }
//la modification en debut d'une liste 
Noeud* modifierEnDebt(Noeud* tete,float prix, float prixth, float moyenne, int quantite, char type[]){
      if(tete=NULL){
         printf("la liste est vide ");
         return NULL;
      }
      tete->prix = prix;
      tete->prixth = prixth;
      tete->moyenne = moyenne;
      tete->quantite = quantite;
      strncpy(tete->type, type, 11);
      tete->type[11] = '\0'; 
      return tete ;
} 


//la modification en fin d'une liste 
Noeud* modifierEfin(Noeud* tete,float prix, float prixth, float moyenne, int quantite, char type[]){
      if(tete=NULL){
         printf("la liste est vide ");
         return NULL;
      }
      Noeud* Courant = tete ; 
      while(Courant->suivant!=NULL)
           Courant=Courant->suivant;
      Noeud* Coursuiv = Courant->suivant ;
      Coursuiv->prix = prix;
      Coursuiv->prixth = prixth;
      Coursuiv->moyenne = moyenne;
      Coursuiv->quantite = quantite;
      strncpy(Coursuiv->type, type, 11);
      Coursuiv->type[11] = '\0';
      return tete ;
      }

           
  
//la modification en milieu d'une liste 
Noeud* modifierEnMilieu(Noeud* tete,int post,float prix, float prixth, float moyenne, int quantite, char type[]){
      if(tete==NULL){
         printf("la liste est vide \n");
         return NULL;
      }
      int taille = tailleNoeud(tete);
      if(post<1 || post>taille){
         printf("la position invalide \n");
         return tete ;
        }
      Noeud* Courant = tete ; 
      for(int i=1 ; i<post ; i++)
         Courant = Courant->suivant;
      Courant->prix = prix;
      Courant->prixth = prixth;
      Courant->moyenne = moyenne;
      Courant->quantite = quantite;
      strncpy(Courant->type, type, 11);
      Courant->type[11] = '\0'; 
      return tete ;
     }
      
