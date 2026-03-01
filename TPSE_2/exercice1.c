#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

// Variable globale : le tableau
int tab[10000];

// Initialise le tableau à zéro
void init_tab() {
    for(int i = 0; i < 10000; i++) tab[i] = 0;
}

// Fonction 1 : Remplit de 0 à 499
void* fonction1(void* arg) {
    for(int i = 0; i < 500; i++) {
        tab[i] = i;
    }
    return NULL;
}

// Fonction 2 : Remplit de 500 à 9999
void* fonction2(void* arg) {
    for(int i = 500; i < 10000; i++) {
        tab[i] = i;
    }
    return NULL;
}

// Vérifie si le tableau est complet (pour l'affichage)
void verifier_tableau(char* titre) {
    printf("\n--- %s ---\n", titre);
    printf("tab[0]  = %d (devrait être 0)\n", tab[0]);
    printf("tab[500] = %d (devrait être 500)\n", tab[500]);
    printf("tab[250]  = %d (devrait être 250)\n", tab[250]);
    printf("tab[5000] = %d (devrait être 5000)\n", tab[5000]);
}

int main() {
    // --- CAS A : PROCESSUS DISTINCTS (fork) ---
    init_tab();
    if (fork() == 0) {
        // Enfant : exécute fonction1
        fonction1(NULL);
        exit(0);
    } else {
        // Parent : exécute fonction2 et attend
        fonction2(NULL);
        wait(NULL);
        verifier_tableau("CAS A : Processus distincts (Chaque processus a sa mémoire)");
        // Résultat : tab[250] sera 0 car le changement est resté chez l'enfant.
    }

    // --- CAS B : THREADS DU MÊME PROCESSUS (pthread) ---
    init_tab();
    pthread_t t1, t2;
    pthread_create(&t1, NULL, fonction1, NULL);
    pthread_create(&t2, NULL, fonction2, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    verifier_tableau("CAS B : Threads du même processus (Mémoire partagée)");
    // Résultat : tab[250] et tab[5000] seront corrects.

    return 0;
}
