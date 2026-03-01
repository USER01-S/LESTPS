#include <iostream>

int main() {
    int N;
    int totalePremiers = 0;
    std::cout << "Saisir un entier N : ";
    std::cin >> N;
        for (int i = 2;i < N ; i++) {
            int premier = 1 ;
            for(int j = 2 ; j*j <= i; j++){
               if (i % j == 0){
               premier = 0;
               break;
                  }
              }
             if(premier){
            std::cout<<i<<"\n";
            totalePremiers++;
                 }
        }
        
        std::cout << "Le nombre de nombres premiers inferieurs ou egaux a " << N << " est : " << totalePremiers << std::endl;

    return 0;
    }

