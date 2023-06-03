#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int duracion=10;
int main(int argc, char *argv[]) {
    srand(time(NULL));
    int n;
    n=atoi(argv[1]);

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
        int duracion = rand() % 31; 
            sleep(duracion);
        if (pid < 0) {
            printf("Error al crear el proceso hijo.\n");
            exit(1);
        } else if (pid == 0) {
            
            printf("Proceso hijo %d creado. PID: %d PPID: %d Duracion: %d\n", i+1, getpid(),getppid(),duracion);
            exit(0);
        }
    }
    sleep(2);
    printf("Todos los procesos hijos han finalizado PID del padre: %d\n",getpid());
    return 0;
}