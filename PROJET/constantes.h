#ifndef CONSTANTES_H
#define CONSTANTES_H
#include <string>

namespace Constantes {
    const int   LARGEUR_FENETRE        = 900;
    const int   HAUTEUR_FENETRE        = 500;
    const float SOL_Y                  = 380.f;
    const float JOUEUR_L               = 70.f;
    const float JOUEUR_H               = 90.f;
    const float JOUEUR_X               = 100.f;
    const float PESANTEUR              = 0.5f;
    const float FORCE_SAUT             = -15.f;
    const float ACCROUPISSEMENT_H      = 45.f;

    const float OBS_L                  = 90.f;
    const float OBS_H_SOL              = 90.f;
    const float OBS_H_AIR              = 100.f;

    const float OBS_SOL_Y              = SOL_Y + JOUEUR_H - OBS_H_SOL;
    const float OBS_AIR_Y              = SOL_Y - 60.f;

    const float DIST_BLOCAGE_SAUT      = 220.f;

    const int   NB_NIVEAUX             = 3;
    const float VITESSE_OBS[3]         = { 4.f,  6.f,  8.f  };
    const float VITESSE_MAX_OBS[3]     = { 8.f, 11.f, 15.f  };
    const int   DUREE_NIVEAU[3]        = { 150,  100,   90   };
    const float DISTANCE_NIVEAU[3]     = { 2500.f, 3000.f, 7000.f };
    const float INTERVALLE_MIN[3]      = { 1.2f,  0.9f,  0.6f };

    const std::string FICHIERS_FOND[3] = {
        "arriereA.jpg.jpeg",
        "arriereB.jpg.jpeg",
        "arriereC.jpg.jpeg"
    };

    const std::string FICHIERS_OBS[3][2] = {
        { "obstA.png",  "obst2A.png"  },
        { "obst2B.png",  "obstB.png"  },
        { "obst2C.png",  "obstC.png"  }
    };

    const std::string NOMS_NIVEAUX[3] = {
        "Niveau 1 - FORET",
        "Niveau 2 - KALAHARI",
        "Niveau 3 - ARCTIQUE"
    };
}
#endif //CONSTANTES_H
