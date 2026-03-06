#include <iostream>
using std :: cout ;
using std :: cin ;
using std :: endl ;
using std :: string ;
int main(){
    string chaine;
    string chainecorreg;
    cout<<"saisir une chaine : \n";
    getline(cin,chaine);
    for(auto &c : chaine){
       ispunct (c);
    }
    cout<<"la nouvel est  chaine : \n"<<chaine<<endl;
    return 0 ;//ispunct ( c ) 
}
