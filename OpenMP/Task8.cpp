#include <omp.h>
#include <iostream>
#include <stdio.h>
#include <time.h>

#define N 500

int main() {

	int matrix[N * N];
	int vector[N];
	int result[N];

	for (int i = 0; i < N * N; i++) {
		matrix[i] = rand() % 10 + 1;
	}
	for (int i = 0; i < N; i++) {
		vector[i] = rand() % 10 + 1;
	}

	int j = 0;

	double start = omp_get_wtime();

#pragma omp parallel for private (j)
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			result[i] += matrix[i * N + j] * vector[j];
	}
	double finish = omp_get_wtime();
	printf("Execution time of a parallel program = %f\n", finish - start);

	start = clock();
	for (int i = 0; i < N; i++) {
		result[i] = 0;
		for (int j = 0; j < N; j++)
			result[i] += matrix[i * N + j] * vector[j];
	}
	finish = clock();
	printf("Execution time of a sequential program = %f\n", (double)(start - finish) / CLOCKS_PER_SEC);
}