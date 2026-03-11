#include <stdio.h>
#include <stdlib.h>
// tableau
#define MAXSIZE 3
typedef struct {
       int lifo[MAXSIZE];
       int top ;
}Pile;
void creePile(Pile* p){
    p->top=-1;
}
int estVide(Pile* p){
    if(p->top==-1)
       return 1 ;
    else 
       return 0;
}
int estPlein(Pile* p){
    if(p->top==MAXSIZE-1)
      return 1;
    else
      return 0 ;
}
void afficher(Pile* p){
    if(estVide(p)){
      printf("Pile est vide ");
      EXIT_FAILURE;
    }
    int i;
    for(i=0;i<p->top+1;i++)
        printf("%d \n",p->lifo[i]);
    printf("\n");
}
void empiler(Pile* p, int element){
    if (estPlein(p)){
       printf("\n débordement \n");
       EXIT_FAILURE;
    }
    else 
      p->lifo[++p->top]=element;
}
int depiler(Pile *p){
    if (p->top == -1){
       printf ("\n Rien à dépiler");
       EXIT_FAILURE;
    }
    else 
       return (p->lifo[p->top--]);
}
int main(){
    Pile* p ;
    creePile(p);
    afficher(p);
    empiler(p,1);
    afficher(p);
    empiler(p,2);
    afficher(p);
    empiler(p,3);
    afficher(p);
    empiler(p,4);
    afficher(p);
    

}
