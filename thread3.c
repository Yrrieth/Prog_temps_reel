#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>

// gcc thread.c -o thread.exe -lpthread
// Ecrire un programme qui créer 2 threads

void* affiche_th (void *num_th) {
	for (int i = 0; i < 10; i++) {
		printf("Thread %ld : %d\n", pthread_self(), i);
		sleep(2);
	}
	pthread_exit(NULL);
}

int main () {
	pthread_t th1, th2;
	pthread_attr_t th_attr;
	struct sched_param param;
	int newprio = 10;

	pthread_attr_init (&th_attr);
	param.sched_priority = newprio;
	pthread_attr_setschedparam(&th_attr, &param);
	pthread_attr_setschedpolicy(&th_attr, SCHED_FIFO);
	pthread_create(&th1, &th_attr, affiche_th, NULL);
	pthread_create(&th2, &th_attr, affiche_th, NULL);
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	pthread_attr_destroy(&th_attr);
	pthread_exit(NULL);
	printf("End process\n");
	return 0;
}