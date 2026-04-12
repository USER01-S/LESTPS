#include"point.hpp"
#include<cmath>
#include<iostream>
using std::cout;

Point::affiche(){
   cout<<"=l'abscisse est : "<<x<<"\n";
   cout<<"=l'ordonnee est : "<<y<<"\n";
}
Point::deplace(double dx , double dy){
    x+=dx;
    y+=dy;
    }
