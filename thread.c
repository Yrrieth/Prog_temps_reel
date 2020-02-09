#include <stdio.h>
#include <pthread.h>

// gcc thread.c -o thread.exe -lpthread

void* somme () {
	int sum = 0;
	for (int i = 0; i < 100; i++)
		sum =+ i;
	printf("Sum == %d\n", sum);
}

int main () {
	pthread_t thr;
	pthread_create(&thr, NULL, somme, NULL);
	pthread_join(thr, NULL);
	printf("End process\n");
	return 0;
}