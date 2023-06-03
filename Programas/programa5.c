#include <stdio.h>
#include <pthread.h>
#define NUM_HILOS 5
int incremento, decremento, op;

struct datos_compartidos
{
    pthread_mutex_t cerrojo;
} datos;

void *codigo_hilio_1(void *id)
{
    pthread_mutex_lock(&datos.cerrojo);
    op = *(int *)id;
    // printf("%d\n",op);
    if (op == 1)
    {
        for (int i = 0; i < 10; i++)
        {
            incremento++;
            printf("%d\n", incremento);
        }
    }
    else if (op == 2)
    {

        for (int i = 0; i < 10; i++)
        {
            decremento--;
            printf("%d\n", decremento);
        }
    }
    pthread_mutex_unlock(&datos.cerrojo);
}
/*void *codigo_hilio_2(void *id)
{
    pthread_mutex_lock(&datos.cerrojo);
    for (int i = 0; i < 10; i--)
    {
        decremento--;
        printf("%d", decremento);
        //code
    }
    pthread_mutex_unlock(&datos.cerrojo);
}*/

void main()
{
    pthread_t hilos[NUM_HILOS];
    int id[NUM_HILOS] = {1, 2};
    int h, m;
    int error;
    error = pthread_mutex_init(&datos.cerrojo, NULL);
    if (error)
    {
        printf("Error al crear el cerrojo");
    }
    else
        for (h = 0; h < NUM_HILOS; h++)
        {
            error = pthread_create(&hilos[h], NULL, codigo_hilio_1, &id[h]);
        }
}