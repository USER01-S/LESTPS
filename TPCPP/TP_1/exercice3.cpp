#include<iostream>
using std::cout;
using std::cin;
using std::endl;
int main (){
    cout<<"le programme est capable de calculer la moyenne pour les nombres positives .  \n";
    int i=0;
    int entier ;
    int somme = 0;
    float moyenne;
   do{
    cout<<"saiser le "<<i+1<<" entiers :";
    cin>> entier;
     if(entier<0){
        cout<<"vous devez saisir un le entiers strictemrnt positive \n";
        }else{
           somme+=entier;
           i++;
           }
   }while(entier != 0 );{
   i-=1;
   cout<<somme<<endl;
   cout<<i<<endl;
   moyenne= (float)somme / i ;
   cout<<"la moyenne de votre sirie est :"<< moyenne <<"\n";
    
   }
   return 0 ;
  
}
