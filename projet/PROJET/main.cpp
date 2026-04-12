// ============================================================
//  JEU DE SFRCH - Mini Projet C++ / SFML
//
//  Compilation (Linux/macOS) :
//    g++ -std=c++17 *.cpp -o jeu -lsfml-graphics -lsfml-window -lsfml-system
//  Contrôles :
//    [ESPACE]       -> Sauter
//     [BAS]   -> Se baisser
//    [ESCAPE]        -> Quitter / Menu
//
//  ASSETS REQUIS (même dossier que l'exécutable) :
//    perso__1_.png  (ou perso.png)
//    arriereA.jpg.jpeg   arriereB.jpg.jpeg   arriereC.jpg.jpeg
//    obstA.png  obst2A.png   obstB.png  obst2B.png   obstC.png  obst2C.png
//    arial.ttf 
// ============================================================

#include "Jeu.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>

int main() {
    try {
        Jeu jeu;
        jeu.lancer();
    } catch (const std::exception& e) {
        std::cerr << "[ERREUR] " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
