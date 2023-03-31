#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define n 500

int global_i = 0;

short A[n][n];
short B[n][n];
int C[n][n];

pthread_mutex_t mutex;

void* runner(void* arg);

int main() {

	srand(time(NULL));

	// ==============================================================================================
	// Matrix Initialization
	// ==============================================================================================

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j] = rand()%100;
			B[i][j] = rand()%100;
		}
	}

	// ==============================================================================================
	// Matrix Multiplication
	// ==============================================================================================

	time_t t;
	t = clock();
	
	pthread_t thread[n];
	for (int i = 0; i < n; i++)
		pthread_create(&thread[i], NULL, runner, NULL);
	for (int i = 0; i < n; i++)
		pthread_join(thread[i], NULL);

	t = clock() - t;
	double duration = ((double)t)/CLOCKS_PER_SEC;

	printf("%f", duration);

	return 0;

}

void* runner(void* arg) {
	pthread_mutex_lock(&mutex);
	int i = global_i++;
	pthread_mutex_unlock(&mutex);
	for (int j = 0; j < n; j++) {
		for (int k = 0; k < n; k++) {
			C[i][j] = A[i][k] * B[k][j];
		}
	}
}
