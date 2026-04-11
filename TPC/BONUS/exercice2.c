#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Date{
     int jour;
     int mois;
     int annee;
}Date;
/*typedef struct Citoyen  {
     char nom[101];
     char adresse[101];
     Date* date;
}Citoyen;*/
typedef struct Citoyen  {
     char nom[101];
     char adresse[101];
     Date* date;
     struct Citoyen* next;
}Citoyen;
typedef struct Ville {
   	Citoyen* first ;
}Ville;
/*void saisir(Citoyen* c){
    if (c->date == NULL) {
        c->date = malloc(sizeof(Date));
    }
    printf("saisir le nom de Citoyen : ");
    scanf("%s",c->nom);
    printf("saisir l'adresse de Citoyen : ");
    scanf("%s",c->adresse);
    printf("saisir la date de naissence de Citoyen \n");
    printf("Jour : ");
    scanf("%d",&(c->date->jour));
    printf("Mois : ");
    scanf("%d",&(c->date->mois));
    printf("Annee : ");
    scanf("%d",&(c->date->annee));
}
void AfficherNouveauxNes(Citoyen tab[],int size){
    for(int i =0 ; i<size; i++){
      if((tab[i].date->annee)>2022){
         printf("NOM : %s\n",tab[i].nom); 
         printf("ADRESSE : %s\n",tab[i].adresse); 
         printf("=====LA DATE DE NAISSENCE ====\n"); 
         printf("JOUR : %d\n",tab[i].date->jour); 
         printf("MOIS : %d\n",tab[i].date->mois);
         printf("ANNEE : %d\n",tab[i].date->annee);  
      }
   }  
}
void AjouterCitoyen(Ville* v, Citoyen* c){
    if(v==NULL){
       v->first=c;
       c->next=NULL;
       }else{
           Citoyen* crt = v->first;
           if(crt!=NULL){
           if((crt->date->annee)>(c->date->annee)){
              c->next=crt;
              crt=c;
              return;
           }else{
             crt->next=c;
           }
           }
           Citoyen* temp = NULL;
           while(crt->next!=NULL){
               if((crt->date->annee)>(c->date->annee)){
                     c->next=crt;
                     crt=c;
                     }
                 }
                 }
   }*/
void AjouterCitoyen(Ville* v, Citoyen* c) {
    // 1. Caso base: La ciudad no existe o el ciudadano es nulo
    if (v == NULL || c == NULL) return;

    // 2. Caso A: La lista está vacía O el nuevo ciudadano va de PRIMERO
    // (Porque su año es menor que el del primer ciudadano actual)
    if (v->first == NULL || c->date->annee < v->first->date->annee) {
        c->next = v->first;
        v->first = c;
        return;
    }

    // 3. Caso B: Buscar el lugar correcto en el medio o al final
    Citoyen* crt = v->first;
    
    // Avanzamos mientras el siguiente no sea NULL Y sea menor al que queremos insertar
    while (crt->next != NULL && crt->next->date->annee < c->date->annee) {
        crt = crt->next;
    }

    // 4. "Cosemos" el nodo en su posición
    c->next = crt->next;
    crt->next = c;
}
void remplirCitoyen(Citoyen* c, char* nome, char* adresse, int j, int m, int a) {
    strcpy(c->nom, nome);
    strcpy(c->adresse, adresse);
    if (c->date == NULL) {
        c->date = (Date*)malloc(sizeof(Date));
    }
    c->date->jour  = j;   // ← was missing
    c->date->mois  = m;   // ← was missing
    c->date->annee = a;   // ← was missing
    c->next = NULL;
}
void afficherVille(Ville v) {
    // 1. Empezamos por el primer ciudadano de la ciudad
    Citoyen* courant = v.first;

    if (courant == NULL) {
        printf("La ville est vide.\n");
        return;
    }

    printf("--- Liste des Citoyens ---\n");
    
    // 2. Recorremos la lista hasta el final
    while (courant != NULL) {
        printf("Nom     : %s\n", courant->nom);
        printf("Adresse : %s\n", courant->adresse);
        
        // Verificamos si la fecha existe antes de imprimirla
        if (courant->date != NULL) {
            printf("Date    : %02d/%02d/%d\n", 
                    courant->date->jour, 
                    courant->date->mois, 
                    courant->date->annee);
        }
        
        printf("--------------------------\n");

        // 3. Saltamos al siguiente ciudadano
        courant = courant->next;
    }
}
int main() {
    Citoyen c1 = {0}, c2 = {0}, c3 = {0}; // ← zero-initialize so date == NULL
    remplirCitoyen(&c1, "Juan",  "Calle 1", 10, 1, 1990);
    remplirCitoyen(&c2, "Maria", "Calle 2", 12, 2, 1994);
    remplirCitoyen(&c3, "Pedro", "Calle 3", 14, 3, 1992);

    Ville v = {NULL};          // ← struct on the stack, not a dangling pointer
    AjouterCitoyen(&v, &c1);
    AjouterCitoyen(&v, &c2);
    AjouterCitoyen(&v, &c3);
    afficherVille(v);
    return 0;
}

