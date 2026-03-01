#include <stdio.h>
void minmax(float* a , float* b){
      if ( *a > *b){
          float s ;
          s = *b ;
          *b = *a ;
          *a = s ;          
      }
}
void trie3nombres(float* a,float* b,float* c){
     minmax(a , b);minmax(a , c);minmax(b, c);
     printf("ordre est  : %.3f < %.3f < %.3f \n", *a , *b , *c);
     }
int main(){
     float a ,b , c ;
     printf("le programme est capable de triant ces trois nombres dans l’ordre croissant\n");
     printf("saiser un  premier nombre : ");
     scanf("%f",&a);
     printf("saiser un  deuxiem nombre : ");
     scanf("%f",&b);
     printf("saiser un  troisiem nombre : ");
     scanf("%f",&c);
     trie3nombres(&a,&b,&c);
     return 0 ; 
}
