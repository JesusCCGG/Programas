#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* hilo_1(void* arg) {
    while (1) {
        printf("Hola desde el hilo 1\n");
        sleep(1);
    }
    pthread_exit(NULL);
}

void* hilo_2(void* arg) {
    while (1) {
        printf("Hola desde el hilo 2\n");
        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t h1, h2;
    int codigo_error1, codigo_error2;

    codigo_error1 = pthread_create(&h1, NULL, hilo_1, NULL);
    codigo_error2 = pthread_create(&h2, NULL, hilo_2, NULL);

    if (codigo_error1 || codigo_error2) {
        printf("Error al crear los hilos\n");
        return 1;
    }

    pthread_join(h1, NULL);
    pthread_join(h2, NULL);

    return 0;
}
