# include <iostream>
# include <list>

using std :: cout ;
using std :: cin ;
using std :: endl ;
using std :: list ;
int main () {
    list <int> entiers ;
    int choix ; 
    int valeur ;  
    do {
       cout<<"\n========================================================\n";
       cout<<"Menu\n";
       cout<<"========================================================\n";
       cout<<"1. Taper 1 pour ajouter un entier dans la liste\n";
       cout<<"2. Taper 2 pour afficher la liste des entiers\n";
       cout<<"3. Taper 3 pour supprimer le dernier entier de la liste\n";
       cout<<"4. Taper 4 pour afficher le dernier entier saisi dans la liste\n";
       cout<<"5. Taper 5 pour Quitter\n";
       cout<<"========================================================\n";
       cout<<"Veuillez saisir votre choix : ";
       cin>>choix;
       switch(choix){
          case 1 :
             cout<<"Veuillez taper l'entier que vous voulez ajouter : ";
             cin>>valeur;
             entiers.push_back (valeur); 
             break ;
          case 2 :
             cout<<"Le contenu de la liste est : ";
             for ( int num : entiers )
                  cout << num << " " ;
             cout << endl ;
             break;
          case 3 :
              cout<<"Vous avez choisi de supprimer le dernier entier de la liste " ;
             entiers.pop_back();
             break;
          case 4 :
             cout<<"le dernier entier saisi dans la liste est : "<<entiers.back()<<endl;
             break;
          case 5:
             cout << "Fin du programme \n" << endl;
             break;
          default :
           cout<<"ERREUR, le numero saisi ne correspond a aucun choix dans la liste.\nReessayez.\n";
       }
       
    }
    while(choix!=5);
return 0;
}
