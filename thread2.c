#include <stdio.h>
#include <pthread.h>
#define N 2

// gcc thread.c -o thread.exe -lpthread
// Ecrire un programme qui créer 2 threads

void* print_thread (void *arg) {
	pthread_t thr;
	for (int i = 0; i < 10; i++)
		printf("th %d : %d\n", (int)arg, i);
}

int main () {
	pthread_t th[N];
	for (int i = 0; i < N; i++) {
		pthread_create(&th[i], NULL, print_thread, (void*) i);
		pthread_join(th[i], NULL);
	}
	printf("End process\n");
	return 0;
}