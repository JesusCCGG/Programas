#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 7) {
        printf("Uso: tuberías -1 orden_1 -2 orden_2 -3 orden_3\n");
        return 1;
    }

    // Crear las tuberías sin nombre
    int pipe1[2];
    int pipe2[2];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        printf("Error al crear las tuberías\n");
        return 1;
    }

    // Crear el primer proceso hijo (orden_1)
    pid_t pid1 = fork();
    if (pid1 == -1) {
        printf("Error al crear el primer proceso hijo\n");
        return 1;
    } else if (pid1 == 0) {
        // Código del primer proceso hijo
        close(pipe1[0]); // Cerrar el extremo de lectura no utilizado

        // Redirigir la salida estándar al extremo de escritura de pipe1
        dup2(pipe1[1], STDOUT_FILENO);
        close(pipe1[1]);

        // Ejecutar el primer comando
        execlp(argv[2], argv[2], NULL);

        // Si la ejecución llega a este punto, indica un error en execlp
        printf("Error al ejecutar el primer comando\n");
        exit(1);
    }

    // Crear el segundo proceso hijo (orden_2)
    pid_t pid2 = fork();
    if (pid2 == -1) {
        printf("Error al crear el segundo proceso hijo\n");
        return 1;
    } else if (pid2 == 0) {
        // Código del segundo proceso hijo
        close(pipe1[1]); // Cerrar el extremo de escritura no utilizado
        close(pipe2[0]); // Cerrar el extremo de lectura no utilizado

        // Redirigir la entrada desde pipe1 al extremo de lectura estándar
        dup2(pipe1[0], STDIN_FILENO);
        close(pipe1[0]);

        // Redirigir la salida estándar al extremo de escritura de pipe2
        dup2(pipe2[1], STDOUT_FILENO);
        close(pipe2[1]);

        // Ejecutar el segundo comando
        execlp(argv[4], argv[4], NULL);

        // Si la ejecución llega a este punto, indica un error en execlp
        printf("Error al ejecutar el segundo comando\n");
        exit(1);
    }

    // Crear el tercer proceso hijo (orden_3)
    pid_t pid3 = fork();
    if (pid3 == -1) {
        printf("Error al crear el tercer proceso hijo\n");
        return 1;
    } else if (pid3 == 0) {
        // Código del tercer proceso hijo
        close(pipe1[0]); // Cerrar el extremo de lectura no utilizado
        close(pipe1[1]); // Cerrar el extremo de escritura no utilizado
        close(pipe2[1]); // Cerrar el extremo de escritura no utilizado

        // Redirigir la entrada desde pipe2 al extremo de lectura estándar
        dup2(pipe2[0], STDIN_FILENO);
        close(pipe2[0]);

        // Ejecutar el tercer comando
        execlp(argv[6], argv[6], NULL);

        // Si la ejecución llega a este punto, indica un error en execlp
        printf("Error al ejecutar el tercer comando\n");
        exit(1);
    }

    // Código del proceso padre
    close(pipe1[0]); // Cerrar el extremo de lectura de pipe1
    close(pipe1[1]); // Cerrar el extremo de escritura de pipe1
    close(pipe2[0]); // Cerrar el extremo de lectura de pipe2
    close(pipe2[1]); // Cerrar el extremo de escritura de pipe2

    // Esperar a que los procesos hijos terminen
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);

    return 0;
}