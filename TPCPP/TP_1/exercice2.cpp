#include <iostream>
using std::cout ;
using std::cin ;
using std::endl;
int main() {
    int N;
    int totalePremiers = 0;
    cout << "Saisir un entier N : ";
    cin >> N;
        for (int i = 2;i < N ; i++) {
            int premier = 1 ;
            for(int j = 2 ; j*j <= i; j++){
               if (i % j == 0){
               premier = 0;
               break;
                  }
              }
             if(premier){
            cout<<i<<"\n";
            totalePremiers++;
                 }
        }
        
        cout << "Le nombre de nombres premiers inferieurs ou egaux a " << N << " est : " << totalePremiers <<endl;

    return 0;
    }

