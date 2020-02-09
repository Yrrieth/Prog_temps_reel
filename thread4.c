#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>

// Ecrire un programme qui lance 6 threads 
// et affiche l'heure du début et de la fin de chaque thread

void print_hour () {
	struct tm instant;
	time_t seconds;
	int data[3];
	time(&seconds);
	instant = *localtime(&seconds);
	data[0] = instant.tm_hour;
	data[1] = instant.tm_min;
	data[2] = instant.tm_sec;
	printf("H:%d m:%d s:%d\n", data[0], data[1], data[2]);
}

void* to_run (void* num_th) {
	int s = 0;

	printf("Thread %ld\n", pthread_self());
	printf("Début : ");
	print_hour();
	for (long int i = 0; i < 1000000; i++) {
		for (long int j = 0; j < 10000; j++) {
			s++;
			//printf("Thread %ld : %ld\n", pthread_self(), i);
		}
		//sleep(1);
	}
	printf("Thread %ld\n", pthread_self());
	printf("Fin : ");
	print_hour();
	pthread_exit(NULL);
}

int main () {

	//pthread_t th1, th2;
	int nb_th = 6;
	int i;

	pthread_t th[nb_th];

	pthread_attr_t th_attr[nb_th];
	struct sched_param param;

	/*pthread_attr_init (&th_attr);
	pthread_attr_setschedpolicy(&th_attr, SCHED_FIFO);

	param.sched_priority = 10;
	pthread_attr_setschedparam(&th_attr, &param);
	pthread_attr_setinheritsched(&th_attr, PTHREAD_EXPLICIT_SCHED);
	pthread_create(&th1, &th_attr, affiche_th, NULL);

	param.sched_priority = 15;
	pthread_attr_setschedparam(&th_attr, &param);
	pthread_create(&th2, &th_attr, affiche_th, NULL);

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	*/

	for (int i = 0; i < nb_th; i++) {
		sleep(i);
		printf("Processus père, crée th %d\n", i);
		pthread_attr_init (&th_attr[i]);
		pthread_attr_setschedpolicy(&th_attr[i], SCHED_FIFO);

		param.sched_priority = (i * 10) + 10;
		pthread_attr_setschedparam(&th_attr[i], &param);
		pthread_create(&th[i], &th_attr[i], to_run, NULL);
	}

	for (i = 0; i < nb_th; i++) {
		pthread_join(th[i], NULL);
	}

	for (int i = 0; i <nb_th; i++) {
		pthread_attr_destroy(&th_attr[i]);	
	}

	printf("End process\n");

	return 0;
}
