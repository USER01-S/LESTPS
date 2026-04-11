// ============================================================
//  JEU DE CACHETTE - Mini Projet C++ / SFML
//
//  Compilation (Linux/macOS) :
//    g++ -std=c++17 main.cpp Jeu.cpp Joueur.cpp Obstacle.cpp ArrierePlan.cpp TexturesObstacles.cpp \
//        -o jeu -lsfml-graphics -lsfml-window -lsfml-system
//
//  Compilation (Windows - MinGW) :
//    g++ -std=c++17 main.cpp Jeu.cpp Joueur.cpp Obstacle.cpp ArrierePlan.cpp TexturesObstacles.cpp \
//        -o jeu.exe -lsfml-graphics -lsfml-window -lsfml-system
//
//  Contrôles :
//    [ESPACE]       -> Sauter
//    [S] ou [BAS]   -> Se baisser
//    [ECHAP]        -> Quitter / Menu
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
