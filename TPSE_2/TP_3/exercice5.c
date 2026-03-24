#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
int main(void)
{
if (fork() == 0)
{
printf("Fin du processus fils de N° %d\n", getpid());
exit(2);
}
//system("ps -l");
sleep(15);

wait(NULL);
}
