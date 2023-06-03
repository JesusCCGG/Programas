#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int pid1,pid2,pid3;
     pid1 = fork();
    if (pid1 == 0)
    {
        system("ls");
        exit(0);
    }
    pid2=fork();
    if (pid2 == 0)
    {
        char *path = "/home/jesuscg/Documents";
        if (chdir(path) == 0)
        {
            system("pwd");
        }
        else
            printf("error de directorio\n");
        
        exit(0);
    }
    pid3=fork();
    if (pid3 == 0)
    {
        system("pwd");
        exit(0);
    }
    printf("\n");
    wait();
    return 0;
}
