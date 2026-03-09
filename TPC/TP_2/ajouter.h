typedef struct Noeud {
    float prix, prixth;
    float moyenne;
    int quantite;
    char type[12];
    struct Noeud* suivant;
} Noeud;





// AJOUTER EN DEBUTE DE LISTE CHAINE 
Noeud* AjouterAdebut(Noeud* tete,float prix, float prixth, float moyenne, int quantite, char type[]){
      Noeud* Nouvnoeud =(Noeud*)malloc(sizeof(Noeud));
      Nouvnoeud->prix = prix;
      Nouvnoeud->prixth = prixth;
      Nouvnoeud->moyenne = moyenne;
      Nouvnoeud->quantite = quantite;
      strncpy(Nouvnoeud->type, type, 11);
      Nouvnoeud->type[11] = '\0'; 
      Nouvnoeud->suivant = NULL;
      if(tete!=NULL){
         Nouvnoeud->suivant=tete;
         tete = Nouvnoeud;
         return tete;
       }      
}



// LA TAILLE DE LISTE CHAINE 
int tailleNoeud(Noeud* tete){
    Noeud* Courant= tete ;
    int taille = 0 ;
    while(Courant!=NULL){
         taille+=1;
         Courant=Courant->suivant;
         }
    return taille ;
    }
    
    
    
    
// AJOUTER EN FIN DE LISTE CHAINE 
Noeud* AjouterEnFin(Noeud* tete,float prix, float prixth, float moyenne, int quantite, char type[]){
      Noeud* Nouvnoeud =(Noeud*)malloc(sizeof(Noeud));
      Noeud* Courant= tete;
      Nouvnoeud->prix = prix;
      Nouvnoeud->prixth = prixth;
      Nouvnoeud->moyenne = moyenne;
      Nouvnoeud->quantite = quantite;
      strncpy(Nouvnoeud->type, type, 11);
      Nouvnoeud->type[11] = '\0'; 
      Nouvnoeud->suivant = NULL;
      if(tete==NULL){
        return Nouvnoeud ;
      }
      while(Courant->suivant != NULL)
            Courant=Courant->suivant;
     Courant->suivant=Nouvnoeud;
     return tete ;
}

//AJOUTER EN MILIEU DE LA LISTE CHAINE
Noeud* AjouterEnMilieu(Noeud* tete,int post ,float prix, float prixth, float moyenne, int quantite, char type[]){
      Noeud* Nouvnoeud =(Noeud*)malloc(sizeof(Noeud));
      Noeud* Courant= tete;
      Nouvnoeud->prix = prix;
      Nouvnoeud->prixth = prixth;
      Nouvnoeud->moyenne = moyenne;
      Nouvnoeud->quantite = quantite;
      strncpy(Nouvnoeud->type, type, 11);
      Nouvnoeud->type[11] = '\0'; 
      Nouvnoeud->suivant = NULL;
      if (Courant == NULL){
         printf("la liste vide");
         return Nouvnoeud;
      }
      int taille = tailleNoeud(tete);
      if(post<1 || post>taille){
         printf("la position est invalide ");
         free(Nouvnoeud);
         return tete ; 
      }
      if(post==1){
         Nouvnoeud->suivant=tete;
         tete=Nouvnoeud;
         return tete ; 
      }
      for(int i = 1 ; i<post-1; i++){
          Courant=Courant->suivant;
          }
      Nouvnoeud->suivant=Courant->suivant;
      Courant->suivant=Nouvnoeud;
      return tete ;
      }
      
      
         
// CREATION D'UN NOEUD DE LISTE CHAINE 
Noeud* creatnoeud(float prix, float prixth, float moyenne, int quantite, char type[]) {
    Noeud* nextNoeud = (Noeud*)malloc(sizeof(Noeud));
    if (nextNoeud == NULL) 
        return NULL;
    nextNoeud->prix = prix;
    nextNoeud->prixth = prixth;
    nextNoeud->moyenne = moyenne;
    nextNoeud->quantite = quantite;
    strncpy(nextNoeud->type, type, 11);
    nextNoeud->type[11] = '\0'; 
    nextNoeud->suivant = NULL;
    return nextNoeud;
}



// AFFICHAGE D'UNE LISTE CHAINE 
void afficher(Noeud* tete) {
    int i = 1 ;
    Noeud* Courant = tete;
    while (Courant != NULL) {
        printf("\n--- Noeud %d ---\n",i);
        printf("Prix: %.2f | HT: %.2f | Moy: %.2f | Qte: %d | Type: %s\n", Courant->prix, Courant->prixth, Courant->moyenne, Courant->quantite, Courant->type);
        Courant = Courant->suivant;
        i++;
    }
    printf("NULL\n");
}
