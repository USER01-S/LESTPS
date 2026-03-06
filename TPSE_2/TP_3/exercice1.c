#include<sys/types.h>
#include<unistd.h> //pour fork()
#include<stdio.h> //pour printf()
#include <stdlib.h>
void main()
{
int i;
i=1;
while (i<=10)
{
       printf("TP LINUX\n");
       sleep(10);
       i=i+1;
   }
}
