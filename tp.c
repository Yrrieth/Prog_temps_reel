// Geoffrey Glaive, Thierry Wen

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct task {
	int pi;
	int ci;
	int di;
	int id; // id de la tâche
	int waiting;
	int response;
} task_t;

// gcc thread.c -o thread.exe -lpthread
// Ecrire un programme qui créer 2 threads

/**
 * Alloue la structure
 */
task_t* alloc_task (int n) {
	task_t* new_task = malloc(n * sizeof(task_t));
	return new_task;
}

/**
 * Affiche les tâches ordonnés selon la priorité de l'algo RM
 * Affiche également le temps de réponse et d'attente
 */
void print_tasks (task_t* tasks, int n) {
	for (int i = 0; i < n; i++) {
		printf("________________________\n");
		printf("Task : %d, pi = %d, ci = %d, di = %d\n", tasks[i].id, tasks[i].pi, tasks[i].ci, tasks[i].di);
		printf("Response time : %d\n", tasks[i].response);
		printf("Waiting rime : %d\n", tasks[i].pi + tasks[i].ci);
	}
}

/**
 * Tri les tâches
 */
void ordonned_task_priority (task_t* tasks, int n) {
	task_t tmp_min;

	tmp_min = tasks[0];
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			if (tasks[j].pi < tmp_min.pi) {
				tmp_min = tasks[j];
				tasks[j] = tasks[i];
				tasks[i] = tmp_min;
			}
		}
	}
}

void clear_response_time (int* rt, int rt_size) {
	for (int i; i < rt[i]; i++) {
		rt[i] = 0;
	}
}

double round (double value) {
	return floor(value + 0.5);
}

void calculate_response_time (task_t* tasks, int n) {
	int rt_size = 100;
	int* rt = malloc(rt_size * sizeof(int));
	int response_time;

	clear_response_time(rt, rt_size);
	
	for (int i = 0; i < n; i++) { // Pour chaque tâche
		rt[i] = tasks[i].ci;
		for (int j = 1; rt[j] != rt[j-1]; j++) { // Pour caculer le temps de réponse
			int k = j;
			double sum = 0;
			while (k > 0) { // On calcule la somme (sigma)
				sum += rt[k - 1]/tasks[k - 1].pi * tasks[j].pi;
				k--;
			}
			sum += tasks[j].ci;
			response_time = (int)round(sum);
			rt[j] = sum;
			tasks[i].response = rt[j];
		}
		clear_response_time(rt, rt_size);
	}
}

/**
 * Demande aux utilisateurs l'ensemble des tâches
 */
void ask_task () {
	int n;
	printf("How many tasks ?\n");
	scanf("%d", &n);

	task_t* tasks = alloc_task(n);
	task_t* tasks_ordonned = alloc_task(n);

	for (int i = 0; i < n; i++) {
		printf("Value of task : %d\n", i);
		printf("Value of Pi ?\n");
		scanf("%d", &tasks[i].pi);
		printf("Value of Ci ?\n");
		scanf("%d", &tasks[i].ci);
		tasks[i].di = tasks[i].pi;
		tasks[i].id = i;
		printf("///////////////////////////\n");
	}

	ordonned_task_priority(tasks, n);
	calculate_response_time(tasks, n);
	print_tasks(tasks, n);
}

int main () {
	ask_task();
	return 0;
}