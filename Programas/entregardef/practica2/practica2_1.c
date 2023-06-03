#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int main() {

    for (int i = 1; i <= 10; i++) {
        pid_t pid = fork();
        
        if (pid < 0) {
            printf("Error al crear el proceso hijo.\n");
            exit(1);
        } else if (pid == 0) {
            
            for (int j = 1; j <= 10; j++)
            {
                sleep(1);
                    printf("%d * %d = %d\n",j,i,i*j);
            
            }
            exit(0);
            printf("\n");
        }
    }
    wait(NULL);
    return 0;
}