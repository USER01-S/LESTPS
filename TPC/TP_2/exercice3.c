#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int individu;
    int occurrences;
} ElementFile;

typedef struct {
    ElementFile *elements;
    int taille;
    int capacite;
} FileAttente;

// Initialise une file d'attente vide
FileAttente* initialiserFile() {
    FileAttente *file = (FileAttente*)malloc(sizeof(FileAttente));
    file->capacite = 2;
    file->taille = 0;
    file->elements = (ElementFile*)malloc(file->capacite * sizeof(ElementFile));
    return file;
}

// Agrandit la capacité de la file si nécessaire
void agrandirFile(FileAttente *file) {
    file->capacite *= 2;
    file->elements = (ElementFile*)realloc(file->elements, file->capacite * sizeof(ElementFile));
}

// Ajoute un individu à la file
void ajouterIndividu(FileAttente *file, int nouvelIndividu) {
    for (int i = 0; i < file->taille; i++) {
        if (file->elements[i].individu == nouvelIndividu) {
            file->elements[i].occurrences++;
            return;
        }
    }
    // Si l'individu n'est pas trouvé, on l'ajoute
    if (file->taille == file->capacite) {
        agrandirFile(file);
    }
    file->elements[file->taille].individu = nouvelIndividu;
    file->elements[file->taille].occurrences = 1;
    file->taille++;
}

// Retire le premier individu de la file
int retirerPremierIndividu(FileAttente *file) {
    if (file->taille == 0) {
        printf("La file est vide !\n");
        return -1;
    }
    int individu = file->elements[0].individu;
    if (file->elements[0].occurrences > 1) {
        file->elements[0].occurrences--;
    } else {
        // Décale les éléments restants
        for (int i = 0; i < file->taille - 1; i++) {
            file->elements[i] = file->elements[i + 1];
        }
        file->taille--;
    }
    return individu;
}

// Affiche la file
void afficherFile(FileAttente *file) {
    printf("[");
    for (int i = 0; i < file->taille; i++) {
        printf("(%d, %d)", file->elements[i].individu, file->elements[i].occurrences);
        if (i < file->taille - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// Libère la mémoire allouée pour la file
void libererFile(FileAttente *file) {
    free(file->elements);
    free(file);
}

int main() {
    FileAttente *file = initialiserFile();

    // Exemple d'utilisation
    ajouterIndividu(file, 9);
    ajouterIndividu(file, 8);
    ajouterIndividu(file, 2);
    ajouterIndividu(file, 2);
    ajouterIndividu(file, 3);
    ajouterIndividu(file, 3);
    ajouterIndividu(file, 3);
    ajouterIndividu(file, 3);
    ajouterIndividu(file, 1);
    ajouterIndividu(file, 8);
    ajouterIndividu(file, 8);
    ajouterIndividu(file, 8);
    ajouterIndividu(file, 8);

    printf("File initiale : ");
    afficherFile(file);

    int premier = retirerPremierIndividu(file);
    printf("Premier individu retiré : %d\n", premier);

    printf("File après retrait : ");
    afficherFile(file);

    libererFile(file);
    return 0;
}
