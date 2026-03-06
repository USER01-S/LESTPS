#include <iostream>
using std :: cout ;
using std :: cin ;
using std :: endl ;
using std :: string ;
int main(){
     string suit ;
     string suittraite;
     cout<<"saisir une chaine : ";
     getline(cin,suit);
     int i = 0 ;
     cout<< suit<<endl;
     while(suit[i] != '\0'){
       if(i<suit.size()){
          if(suit[i]==' '){
             suit[i]=' ';
          }else{
                suit[i]+=1;
          
          }
         }
         i++;
     }
     cout<< suit<<endl;
}
