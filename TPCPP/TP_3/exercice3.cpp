#include <iostream>
#include <cmath>
using std::cout;
using std::cin;
using std::endl;
double racine(double x, bool ok=true){
    if(x<=2 && x>=1 ){
        cout<<"la fonction est definie au point "<<x<<endl;
        double a =std::sqrt((x-1)*(2-x));
        cout<<"f("<<x<<") = "<<a<<endl;
        return a ;
      }else{
         cout<<"la fonction n'est pas definie au point \n"<< x<<"\n";
         return 0;
         }
}
int main(){
    double y ;
    cout<<"taper un double : ";
    cin>>y;
    racine(y);


   return 0 ;
   }
