#include <iostream>
using std :: cout ;
using std :: cin ;
using std :: endl ;
using std :: string ;
int main(){
    string chaine;
    cout<<"saisir une chaine : ";
    getline(cin,chaine);
    for (int i = 0; i < chaine.size(); i++) {
        if (ispunct(chaine[i])) {
            chaine.erase(chaine.begin()+ i);
            i--;// ne pass une caractere apres la supprission car le suit de  i est i apres la supprission
    }
}
    cout<<"Votre chaine apres exculusion des caractères spéciaux: "<<chaine<<endl;
    return 0 ;
}
