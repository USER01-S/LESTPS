#include<iostream>
using std::cout;
using std::cin;
using std::endl;
int valeurTaper;
void Menu(){
  cout<<"=============================================================\n";
   cout<<"                            Menu                             \n";
    cout<<"=============================================================\n";
   cout<<"1. Taper 1 pour incrémenter l’entier par un \n";
   cout<<"2. Taper 2 pour décrémenter l’entier par 2\n";
   cout<<"3. Taper 3 pour multiplier l’entier par 10\n";
   cout<<"4. Taper 4 pour quitter\n";
   cout<<"votre choix :";
   cin>>valeurTaper;
}
int main(){
    int valuer ;
    do {
       cout<<"saiser une valeur entier de votre choix ";
       cin>>valuer;
       cout<<"votre valeur est :"<<valuer<<endl;
       Menu();
      switch(valeurTaper){
         case 1 :
         valuer+=1;
         cout<<"votre nouvel valeur est :"<<valuer<<"\n\n\n";

         break;
         case 2 :
         valuer-=2;
         cout<<"votre nouvel valeur est :"<<valuer<<"\n\n\n";

         break;
         case 3 :
         valuer*=10;
         cout<<"votre nouvel valeur est :"<<valuer<<"\n\n\n";
         break;
         case 4 :
         printf("Fin du programme. Au revoir !\n");
         break;
         default:
         printf("votre choix invalide , doit taper l'un des [1,2,3,4]\n");
         break;
     }
    }while(valeurTaper !=4);
   return 0 ; 
}
