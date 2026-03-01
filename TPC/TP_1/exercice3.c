#include <stdio.h>
int heure , minutes ;
void DecoupeMinutes(int* heure , int* minutes){
    if(*minutes >= 60){
         int a , b;
         a = *minutes / 60 ;
         b = *minutes % 60 ;
         *heure += a ;
         *minutes = b ;     
    }
}
void NouvelleHeure (int* heure , int* minutes){
     *minutes = 15 ;
     DecoupeMinutes(heure ,minutes);
}
void affichage(){
    printf("______ la nouvelle heure est ' %d:%d  ' ______\n",heure,minutes);
}
int main (){
    printf("saiser les  heures : ");
    scanf("%d",&heure);
    printf("saiser les minutes : ");
    scanf("%d",&minutes);
    DecoupeMinutes(&heure ,&minutes);
    affichage();
    NouvelleHeure (&heure ,&minutes);
    affichage();
}
