#include <iostream>
using namespace std;

int main() {
   string suit;
   cout << "saisir une chaine : ";
   getline(cin, suit);
   cout << suit << endl;
   int i = 0;
   while (suit[i] != '\0') {
      if (i < suit.size()) {
         if (suit[i] == ' ') {
            suit[i] = ' ';  // espace conservé
         } else {
            suit[i] += 1;  // décalage d'un caractère ASCII
         }
      }
      i++;
   }
   cout << suit << endl;
}
