#include <iostream>
using std :: cout ;
using std :: cin ;
using std :: endl ;
using std :: string ;
int main(){
    string chaine ; 
    cout <<" Saisir une chaine : ";
    getline(cin,chaine);
    string copyee;
    int taille =chaine.size() ;
    for(int i =0 ; i < taille ; i++){
            copyee += chaine[taille-i-1];
       }
    chaine=copyee;
    cout<<"Votre chaine apres traitement : "<<chaine<<endl;
}
