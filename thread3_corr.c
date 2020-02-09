#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>

// gcc thread.c -o th -lpthread
// Ecrire un programme qui créer 2 threads

// Pour éxecuter, il faut les droits administrateurs
// sudo ./th
// Car on modifie les threads du système et non ceux du processus père 

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

	pthread_attr_init (&th_attr);
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
	pthread_attr_destroy(&th_attr);
	printf("End process\n");
	return 0;
}
