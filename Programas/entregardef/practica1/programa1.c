#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Mal uso\n");
        return 1;
    }

    printf("%s\n", argv[1]);
    char *opc = argv[1];

    if (strcmp(opc, "-l") == 0)
    { // execl
        execl("/bin/ls", "ls", "-al", "/usr/bin", (char *)NULL);
    }
    else if (strcmp(opc, "-v") == 0)
    { // execv
        char *args[] = {"ls", "-al", "/usr/bin", NULL};
        execv("/bin/ls", args);
    }
    else if (strcmp(opc, "-le") == 0)
    { // execle
        char *envp[] = {"PATH=bin:/usr/bin", NULL};
        execle("/bin/ls", "ls", "-al", "/usr/bin", (char *)NULL, envp);
    }
    else
    {
        printf("Opcion no valida\n");
    }

    return 0;
}
