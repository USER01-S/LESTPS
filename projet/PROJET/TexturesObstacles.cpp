#include "TexturesObstacles.h"
#include "constantes.h"
#include <iostream>

void TexturesObstacles::charger() {
    for (int i = 0; i < Constantes::NB_NIVEAUX; ++i) {
        solCharge[i]    = sol[i].loadFromFile(Constantes::FICHIERS_OBS[i][0]);
        aerienCharge[i] = aerien[i].loadFromFile(Constantes::FICHIERS_OBS[i][1]);
        if (!solCharge[i])
            std::cerr << "[AVERT] Impossible de charger '"
                      << Constantes::FICHIERS_OBS[i][0] << "'\n";
        if (!aerienCharge[i])
            std::cerr << "[AVERT] Impossible de charger '"
                      << Constantes::FICHIERS_OBS[i][1] << "'\n";
    }
}
