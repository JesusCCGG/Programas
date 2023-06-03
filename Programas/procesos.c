#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Uso: %s <numero_procesos>\n", argv[0]);
        return 1;
    }

    int num_procesos = atoi(argv[1]);

    // Semilla para generar números aleatorios
    srand(time(NULL));

    int i;
    pid_t pid;

    for (i = 0; i < num_procesos; i++)
    {
        pid = fork();

        if (pid < 0)
        {
            // Error al crear el proceso hijo
            printf("Error al crear el proceso hijo.\n");
            return 1;
        }
        else if (pid == 0)
        {
            // Código del proceso hijo

            int duracion = rand() % 31; // Generar duración aleatoria entre 0 y 30 segundos
            sleep(duracion);

            printf("Proceso hijo PID: %d, PPID: %d, Duración: %d segundos.\n", getpid(), getppid(), duracion);

            return 0;
        }
    }

    // Código del proceso padre
    for (i = 0; i < num_procesos; i++)
    {
        int status;
        pid_t child_pid = wait(&status);

        if (WIFEXITED(status))
        {
            printf("Proceso hijo terminado: PID: %d, PPID: %d. Duración: %d segundos.\n", child_pid, getpid(), WEXITSTATUS(status));
        }
        else
        {
            printf("Proceso hijo terminado de manera anormal: PID: %d, PPID: %d.\n", child_pid, getpid());
        }
    }

    return 0;
}
