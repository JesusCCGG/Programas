#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // if (argc != 2)
    // {
    //     printf("Mal uso\n");
    //     return 1;/bin
    // }
    
      //  printf("%s\n", argv[1]);
        char *opc=argv[1];

        char *args[] = {"ls","-al","/usr/bin",NULL};
        execv("/bin/echo", args);        
        printf("Error\n");
    return 0;
}
