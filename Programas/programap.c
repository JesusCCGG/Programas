#include<stdio.h>
#include<pthread.h>
// Declaración de datos compartidos y el cerrojo que los protege
struct datos_compartidos
{
    // Declaracióndelosdatos
        int inc;
        // Declaracióndelcerrojo
        pthread_mutex_t cerrojo;
}datos;
void codigo_hilo_1(void *arg)
{
    pthread_mutex_lock(&datos.cerrojo);
    // Seccióncrítica
    printf("1");
    // Accesoalosdatoscompartidos
    pthread_mutex_unlock(&datos.cerrojo);
    -
}
void codigo_hilo_2(void *arg)
{
    pthread_mutex_lock(&datos.cerrojo);
    // Seccióncrítica
    // Accesoalosdatoscompartidos
    pthread_mutex_unlock(&datos.cerrojo);
}
void main()
{
    pthread_t hilo_1, hilo_2;
    int error;

    // Inicializacióndelcerrojo
     pthread_mutex_init(&datos.cerrojo, NULL);
   
        // Tratamientodelerror

        // Creacióndeloshilos
        pthread_create(&hilo_1, NULL, codigo_hilo_1, NULL);
    // Tratamientodelerror
         pthread_create(&hilo_2, NULL, codigo_hilo_2, NULL);
    // Tratamientodelerror
    
}