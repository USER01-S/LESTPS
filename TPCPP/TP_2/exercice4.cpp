#include <iostream>
using std :: cout ;
using std :: cin ;
using std :: endl ;
using std :: string ;
int main(){
    string s1 ; 
    cout <<"Saisir une chaine : ";
    getline(cin,s1);
    if(s1.empty()){
      cout<<"Chaine initialiser par les parametres par defaut\n";
      s1.append("Module Programmation C Avancee \n");
       }else{
            cout<<"Chaine n'est Pas vide !!\n";
       }
    cout<<s1<<endl;
    string s2 ;
    s2+=toupper(s1[0]);
    int i =s1.find(' ');
    while(s1[i] !='\0'){
          if(i + 1 < s1.size())
            s2 += toupper(s1[i+1]);

        i = s1.find(' ', i + 1);
    }
    cout<<"s2 est :"<<s2<<endl;
    i=s1.find("C Avancee");
    s1=s1.replace(i,i," POO C++");
    cout<<s1<<endl;
    return 0 ;
    }
