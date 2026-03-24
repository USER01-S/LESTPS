#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void) {
int pid;
printf("Bonjour … ") ;
pid = fork();
switch (pid) {
case -1:
printf("Erreur: echec du fork() \n");
exit(1);
break;
case 0:
printf("je suis le processus fils : PID=%d , mon pere est : PPID=%d\n",
getpid(), getppid() );
exit(0);
break;
default:
printf("Ici le pere: le fils a un pid=%d\n", pid );
wait(0); /* attente de la fin du fils */
printf("Fin du pere.\n");
}
}
