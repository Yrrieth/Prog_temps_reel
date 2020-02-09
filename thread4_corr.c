#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>

void* func(void* arg) {
	long int num = (long int) arg;
	sleep(num);
	struct tm instant;
	time_t seconds;
	int data[3];
	time(&seconds);
	instant = *localtime(&seconds);
	data[0] = instant.tm_hour;
	data[1] = instant.tm_min;
	data[2] = instant.tm_sec;
	printf("Début thread %ld : %d:%d:%d\n", num, data[0], data[1], data[2]);

	for (long int i = 0; i < 100000; i++) {
		for (long int j = 0; j < 1000; j++) {

		}
	}

	time(&seconds);
	instant = *localtime(&seconds);
	data[0] = instant.tm_hour;
	data[1] = instant.tm_min;
	data[2] = instant.tm_sec;
	printf("Fin thread %ld : %d:%d:%d\n", num, data[0], data[1], data[2]);
	pthread_exit(NULL);
}

int main () {
	int nb_th = 6;
	int i;

	pthread_t th[nb_th];

	pthread_attr_t th_attr;
	struct sched_param param;

	pthread_attr_init (&th_attr);
	pthread_attr_setinheritsched(&th_attr, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&th_attr, SCHED_FIFO);

	for (int i = 0; i < nb_th; i++) {
		param.sched_priority = (i + 1) * 10;
		pthread_attr_setschedparam(&th_attr, &param);
		pthread_create(&th[i], &th_attr, func, (void*)i);
	}

	for (i = 0; i < nb_th; i++) {
		pthread_join(th[i], NULL);
	}

	pthread_attr_destroy(&th_attr);

	printf("End process\n");
}