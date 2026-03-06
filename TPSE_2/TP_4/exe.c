#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main()
{
int i;
i=3;
int id;
id=fork();
if (id ==0)
{
i=10;
printf("%d\n",i);

fork();
i=1;
}
wait(NULL);
printf("%d\n",i) ;
i=5;
printf("%d\n",i);
return 0;
}
