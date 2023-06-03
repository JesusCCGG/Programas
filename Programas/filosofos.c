#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define N 5
#define PENSANDO 2
#define HAMBRIENTO 1
#define COMIENDO 0
#define IZQUIERDA (fil_num + 4) % N
#define DERECHA (fil_num + 1) % N

int estado[N];
int filo[N] = { 0, 1, 2, 3, 4 };

sem_t mutex;
sem_t S[N];

void prueba(int fil_num)
{
	if (estado[fil_num] == HAMBRIENTO
		&& estado[IZQUIERDA] != COMIENDO
		&& estado[DERECHA] != COMIENDO) {
		// estado that COMIENDO
		estado[fil_num] = COMIENDO;

		sleep(2);

		printf("El filosofo %d toma el tenedor %d y %d\n",
					fil_num + 1, IZQUIERDA + 1, fil_num + 1);

		printf("El filosofo %d esta comiendo\n", fil_num + 1);

		// sem_post(&S[fil_num]) has no effect
		// during takefork
		// used to wake up HAMBRIENTO filosofos
		// during putfork
		sem_post(&S[fil_num]);
	}
}

// take up chopsticks
void take_fork(int fil_num)
{

	sem_wait(&mutex);

	// estado that HAMBRIENTO
	estado[fil_num] = HAMBRIENTO;

	printf("El filosofo %d esta hambriento\n", fil_num + 1);

	// eat if neighbours are not COMIENDO
	prueba(fil_num);

	sem_post(&mutex);

	// if unable to eat wait to be signalled
	sem_wait(&S[fil_num]);

	sleep(1);
}

// put down chopsticks
void put_fork(int fil_num)
{

	sem_wait(&mutex);

	// estado that PENSANDO
	estado[fil_num] = PENSANDO;

	printf("El filosofo %d poniendo el tenedor %d y %d abajo\n",
		fil_num + 1, IZQUIERDA + 1, fil_num + 1);
	printf("El filosofo %d esta pensando \n", fil_num + 1);

	prueba(IZQUIERDA);
	prueba(DERECHA);

	sem_post(&mutex);
}

void* filosofo(void* num)
{

	while (1) {

		int* i = num;

		sleep(1);

		take_fork(*i);

		sleep(0);

		put_fork(*i);
	}
}

int main()
{

	int i;
	pthread_t thread_id[N];

	// initialize the semaphores
	sem_init(&mutex, 0, 1);

	for (i = 0; i < N; i++)

		sem_init(&S[i], 0, 0);

	for (i = 0; i < N; i++) {

		// create filosofo processes
		pthread_create(&thread_id[i], NULL,
					filosofo, &filo[i]);

		printf("El filosofo %d esta pensando\n", i + 1);
	}

	for (i = 0; i < N; i++)

		pthread_join(thread_id[i], NULL);
}
