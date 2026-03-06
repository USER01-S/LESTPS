#include <iostream>
using std :: cout ;
using std :: cin ;
using std :: endl ;
using std :: string ;

int main (){
   string chane ;
   cout <<"Saisir une chaine : ";
   cin >> chane ;
   for (auto &c : chane ){
      if ( c == std::toupper(c)){
         c = std::tolower(c);
         }else{
         c = std::toupper(c); 
        }
   }
  cout<< "Votre chaine apres traitement : " <<chane << endl;
   return 0 ; 
}
