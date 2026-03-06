#include <iostream>
#include <limits>
using std :: cout ;
using std :: cin ;
using std :: endl ;
using std :: string ;

int main (){
    string chaine , chaine1 ;
   cout <<"Saisir une chaine : " ;
   getline(cin,chaine); 
   int compter = 0 ; 
   for(auto c : chaine ){
       c = std::tolower(c);
       switch(c){
         case 'a':
            compter+=1;
            break ; 
         case 'e':
             compter+=1;
            break ; 
         case 'i':
            compter+=1;
            break ; 
         case 'o': 
            compter+=1;
            break ; 
         case 'u': 
            compter+=1;
            break ; 
         case 'y':
            compter+=1;
            break ; 
         default:
            break ;
       }
   }
   cout<<"Nombre de voyelles : "<< compter<<endl;
   cout<<"Saisir une chaine : ";
   cin.ignore(std :: numeric_limits < std :: streamsize >::max (),'\n');
   getline(cin,chaine1);
   int compter1 = 1 ; 
   for(auto c : chaine1){
       if(c == ' '){
          compter1+=1;
          }
        }
   cout<<"nombre de mot dans votre chaine : "<< compter1<<endl;    
   return 0 ; 
}
