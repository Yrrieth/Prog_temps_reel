#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// gcc thread.c -o thread.exe -lpthread
// Ecrire un programme qui créer 2 threads

void* affiche_th (void *num_th) {
	for (int i = 0; i < 10; i++) {
		printf("Thread %ld : %d\n", pthread_self(), i);
		sleep(2);
		pthread_exit(NULL);
	}
}

int main () {
	pthread_t th1, th2;
	pthread_create(&th1, NULL, affiche_th, NULL);
	pthread_create(&th2, NULL, affiche_th, NULL);
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	pthread_exit(NULL);
	printf("End process\n");
	return 0;
}