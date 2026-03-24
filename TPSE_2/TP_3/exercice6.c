/*#include <unistd.h>
int main(void) {
    char *argv[] = {"ls", "-l", "/home", NULL};
    execv("/bin/ls", argv);  // chemin complet obligatoire
    return 0;
}*/
/* #include <unistd.h>
int main(void) {
    char *argv[] = {"ls", "-l", "/home", NULL};
    execvp("ls", argv);  // pas besoin de /bin/ls
    return 0;
} */
/*  #include <unistd.h>
int main(void) {
    char *argv[] = {"ls", "-l", NULL};
    char *envp[] = {"PATH=/bin", "USER=root", NULL};
    execve("/bin/ls", argv, envp);  // environnement défini manuellement
    return 0;
}*/
/* #include <unistd.h>
int main(void) {
    execl("/bin/ls", "ls", "-l", "/home", NULL);  // args en liste, NULL obligatoire à la fin
    return 0;
} */
/* #include <unistd.h>
int main(void) {
    execlp("ls", "ls", "-l", "/home", NULL);  // pas besoin de /bin/ls
    return 0;
} */
/* #include <unistd.h>
int main(void) {
    char *envp[] = {"PATH=/bin", "LANG=fr_FR", NULL};
    execle("/bin/ls", "ls", "-l", "/home", NULL, envp);
    return 0;
} */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    char *argv[] = {"ls", "-l", "/home", NULL};

    if (fork() == 0) {
        // Fils : exécute ls -l /home
        execvp("ls", argv);
        perror("execvp échoué");  // affiché seulement si exec échoue
    } else {
        // Père : attend la fin du fils
        wait(NULL);
        printf("Fils terminé.\n");
    }
    return 0;
}
