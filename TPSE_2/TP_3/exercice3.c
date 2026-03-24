#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    printf("=== PROCESSUS INITIAL ===\n");
    printf("PID  : %d\n", getpid());
    printf("PPID : %d\n\n", getppid());

    pid = fork();

    if (pid < 0) {
        perror("fork échoué");
        exit(1);
    }

    /* ───── PROCESSUS ENFANT ───── */
    if (pid == 0) {
        printf("=== ENFANT (avant orphelinat) ===\n");
        printf("Mon PID   : %d\n", getpid());
        printf("Mon PPID  : %d (c'est le père)\n\n", getppid());

        /* Le père va mourir, on attend un peu */
        sleep(2);

        printf("=== ENFANT (après orphelinat) ===\n");
        printf("Mon PID   : %d\n", getpid());
        printf("Mon PPID  : %d (adopté par init !)\n\n", getppid());

        sleep(1);
        printf("Enfant terminé.\n");
        exit(0);
    }

    /* ───── PROCESSUS PÈRE ───── */
    else {
        printf("=== PÈRE ===\n");
        printf("Mon PID        : %d\n", getpid());
        printf("PID de l'enfant: %d\n", pid);
        printf("Le père se termine SANS attendre l'enfant...\n\n");

        /* Le père meurt volontairement sans wait() */
        /* L'enfant devient orphelin → adopté par init (PID 1) */
        exit(0);
    }

    return 0;
}
