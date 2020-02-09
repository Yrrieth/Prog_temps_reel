#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>

/**
 * Ecrire un programme qui lance 3 threads
 * selon les paramètres suivants :
 * 
 * Tâche         |  Ai  |  Pi  |  Algorithme
 * T1            |  0   |  20  |
 * T2            |  2   |  40  |  FIFO
 * T3            |  4   |  60  |
 *
 * et affiche l'heure du début et de la fin de chaque thread
 *
 * Run :
 * $ gcc thread.c -o thread.exe -lpthread
 */

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
	int* nt = num_th;

	printf("Thread n° : %d, %ld\n", *nt, pthread_self());
	printf("Début : ");
	print_hour();
	printf("\n\n");
	for (long int i = 0; i < 1000000; i++) {
		for (long int j = 0; j < 10000; j++) {
			s++;
		}
	}
	printf("Thread n° : %d, %ld\n", *nt, pthread_self());
	printf("Fin : ");
	print_hour();
	printf("\n\n");
	pthread_exit(NULL);
}

int main () {

	int nb_th = 3;
	int k[3];
	int i;

	pthread_t th[nb_th];

	pthread_attr_t th_attr[nb_th];
	struct sched_param param;

	for (int i = 0; i < nb_th; i++) {
		sleep(2);
		k[i] = i;
		pthread_attr_init (&th_attr[i]);
		pthread_attr_setschedpolicy(&th_attr[i], SCHED_FIFO);

		param.sched_priority = (i * 10) + 20;
		pthread_attr_setschedparam(&th_attr[i], &param);
		pthread_create(&th[i], &th_attr[i], to_run, k + i);
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
