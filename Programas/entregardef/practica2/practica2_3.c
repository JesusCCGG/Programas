#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    
    int pid1,pid2,pid3;

    pid1 = fork();
    if (pid1 == 0)
    {
        system("mkdir NuevaCarpeta");
        exit(0);
    }
    pid2 = fork();
    if (pid2 == 0)
    {
    sleep(1);
        char *path = "/home/jesuscg/Documents/Programas/NuevaCarpeta";

        if (chdir(path) == 0)
        {
           
            system("touch Archivo");
        }
        else
            printf("error de directorio 2\n");
        exit(0);
    }
    pid3 = fork();
    if (pid3 == 0)
    {
        sleep(2);
        char *path = "/home/jesuscg/Documents/Programas/NuevaCarpeta";
        if (chdir(path) == 0)
        {
            system("echo holaxd > Archivo");
        }
        else
            printf("error de directorio 3\n");
        exit(0);
    }
    
    return 0;
}
