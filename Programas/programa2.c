#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define SEM_HIJO 0
#define SEM_PADRE 1
main(int argc, char *argv[])
{
    int i = 10, semid, pid;
    struct sembuf operacion;
    key_t llave;

    /*Peticion de un identificador con dos semáforos*/
    llave = ftok(argv[0], 'K');
    if ((semid = semget(llave, 2, /* code */ IPC_CREAT | 0600)) == -1)
    {
        perror("semget");
        //exit(-1);
    }
    /*Inicializacion de semáforos.*/
    /*Cerramos el semáforo del proceso hijo.*/
    semctl(semid, SEM_HIJO, SETVAL, 0);
    /*Cerramos el semáforo del proceso hijo.*/
    semctl(semid, SEM_PADRE, SETVAL, 1);

    /*Creacion del proceso hijo.*/
    if ((pid = fork()) == -1)
    {
        perror("fork");
        //exit(-1);
    }
    else if (pid == 0)
    {
        while (i)
        {
            /* Cerramos el semáforo del proceso hijo */
            operacion.sem_num = SEM_HIJO;
            operacion.sem_op = -1;
            operacion.sem_flg = 0;
            semop(semid, &operacion, 1);

            printf("PROCESO HIJO: %d\n", i--);

            /*Abrimos el semaforo del proceso padre*/
            operacion.sem_num = SEM_PADRE;
            operacion.sem_op = -1;
            operacion.sem_flg = 0;
            semop(semid, &operacion, 1);
        }
        /*Borrado del semáforo*/
        semctl(semid, 0, IPC_RMID, 0);
    }
    else
    { /*Código del proceso padre*/
        operacion.sem_flg = 0;
        while (i)
        {
            /*Cerramos el semáforo*/
            operacion.sem_num = SEM_PADRE;
            operacion.sem_op = -1;
            semop(semid, &operacion, 1); /* code */

            printf("PROGRESO PADRE: %d\n", i--);

            /*Abrimos el semáforo del proceso hijo.*/
            operacion.sem_num = SEM_HIJO;
            operacion.sem_op = 1;
            semop(semid, &operacion, 1);
        }    
        /*Borrado del semáforo*/
        semctl(semid, 0, IPC_RMID, 0);
    }   
}