#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define n 500

int main() {

	srand(time(NULL));

	// ==============================================================================================
	// Matrix Initialization
	// ==============================================================================================

	short A[n][n];
	short B[n][n];
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

	int C[n][n];
	#pragma omp parallel for num_threads(7)
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			C[i][j] = 0;
			for (int k = 0; k < n; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}

	t = clock() - t;
	double duration = ((double)t)/CLOCKS_PER_SEC;

	printf("%f", duration);



	return 0;

}
