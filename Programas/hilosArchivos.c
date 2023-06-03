//programa que relize la escritura de un archivo por medio de un hilo y por medio de otro hilo, lea el archivo en lenguaje c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *escribir_archivo(void *arg);
void *leer_archivo(void *arg);

int main()
{
    pthread_t hilo_escritura, hilo_lectura; //creacion de los hilos

    // Creamos el hilo de escritura
if (pthread_create(&hilo_escritura, NULL, escribir_archivo, NULL))
{
        fprintf(stderr, "Error al crear el hilo de escritura\n");
        exit(1);
}

    // Crear el hilo de lectura
if (pthread_create(&hilo_lectura, NULL, leer_archivo, NULL))
{
        fprintf(stderr, "Error al crear el hilo de lectura\n");
        exit(1);    }

// Esperar a que los hilos terminen
pthread_join(hilo_escritura, NULL);
pthread_join(hilo_lectura, NULL);

return 0;
}

void *escribir_archivo(void *arg)
{
    FILE *archivo;

    // Abre el archivo para su escritura
    archivo = fopen("archivo.txt", "w");
    if (archivo == NULL)
{
        fprintf(stderr, "Error al abrir el archivo para la escritura\n");
    exit(1);
}

    // Escribir en el archivo
fputs("Este es el mensaje", archivo);

    // Cerrar el archivo
fclose(archivo);

    return NULL;
}

void *leer_archivo(void *arg)
{
    FILE *archivo;
    char buffer[100];

    // Abrir el archivo para lectura
    archivo = fopen("archivo.txt", "r");
    if (archivo == NULL)
{
        fprintf(stderr, "Error al abrir el archivo para la lectura\n");
        exit(1);
}

    // Leer el contenido del archivo
fgets(buffer, sizeof(buffer), archivo);
    // Imprimir el contenido del archivo
printf("Contenido del archivo: %s\n", buffer);

    // Cerrar el archivo
fclose(archivo);

    return NULL;
}
//Este programa utiliza las funciones pthread_create() y pthread_join()  para crear y esperar a la finalización de los hilos.
// La función escribir_archivo() escribe en el archivo "archivo.txt" utilizando la función fputs(),
// mientras que la función leer_archivo() lee el contenido del archivo utilizando la función fgets() y lo imprime por pantalla utilizando printf().
