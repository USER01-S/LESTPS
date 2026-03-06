#include <stdio.h>
#include <stdlib.h>

typedef struct {
       float prix , prixth ;
       float moyenne ;
       int quantite ;
       char type[12];
       Element* suivant ;

}Element;
void sasairElement(Element element){
     printf("saiser le prix d'element : ");
     scanf("%f",&element.prix);
     printf("saiser le prixht d'element : ");
     scanf("%f",&element.prixth);
     printf("saiser le moyenne  d'element : ");
     scanf("%f",&element.moyenne);
     printf("saiser la quantite  d'element : ");
     scanf("%d",&element.quantite);
     printf("saiser le type d'element : ");
     scanf("%s",element.type);
}
Liste* initialisation() {
    Liste* liste = malloc(sizeof(liste));
    Element* element= malloc(sizeof(Element));
    element->prix = 0;
    element->suivant = null;
    liste->premier = element;
    return liste;
}
int main (){
     Element element ;
     sasairElement(element);
}
