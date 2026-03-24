#include <iostream>
using std::cout;
using std::cin;
using std::endl;
void echanger(int a , int b){
   int c = a;
   a=b ;
   b=c ;
}
void echangerref(int &a , int &b){
   int c = a;
   a=b ;
   b=c ;
}
void echangerpointeur(int *a , int *b){
   int c = *a;
   *a=*b ;
   *b=c ;
}
int main(){
    int a ,b;
    cout<<"saisir l'entier A : ";
    cin>>a;
    cout<<"saisir l'entier B : ";
    cin>>b;
    cout<<"===========================";
    cout<<" Par passage valeur ";
    cout<<"===========================\n";
    cout<<"avant d'appel  de la fonction : ";
    cout<<"a= "<<a<<"  b= "<<b<<"\n";
    cout<<"apres l'appel de fonction : ";
    echanger(a, b);
    cout<<"a= "<<a<<"  b= "<<b<<"\n\n";
    cout<<"==========================";
    cout<<" Par passage reference ";
    cout<<"===========================\n";
    cout<<"avant d'appel  de la fonction : ";
    cout<<"a= "<<a<<"  b= "<<b<<"\n";
    cout<<"apres l'appel de fonction : ";
    echangerref(a, b);
    cout<<"a= "<<a<<"  b= "<<b<<"\n\n";
    cout<<"==========================";
    cout<<" Par passage pointeur ";
    cout<<"===========================\n";
    cout<<"avant d'appel  de la fonction : ";
    cout<<"a= "<<a<<"  b= "<<b<<"\n";
    cout<<"apres l'appel de fonction : ";
    echangerpointeur(&a, &b);
    cout<<"a= "<<a<<"  b= "<<b<<"\n";
    }
