#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    int signalNumber = atoi(argv[1]);
    pid_t pid = atoi(argv[2]);

    if (kill(pid, signalNumber) == -1) {
        printf("Error al enviar la señal al proceso %d\n", pid);
        return 1;
    }
    printf("Señal enviada correctamente al proceso %d\n", pid);
    return 0;
}