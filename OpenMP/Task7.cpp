#include <omp.h>
#include <iostream>
#include <stdio.h>


int main() {
	int a[12], b[12], c[12];
#pragma omp parallel num_threads(3)
	{
#pragma omp for schedule(static)
		for (int i = 0; i < 12; i++) {
			a[i] = rand() %10 + 1;
			printf("A[%d] = %d\n", i, a[i]);
			b[i] = rand() % 10 + 1;
			printf("B[%d] = %d\n", i, b[i]);
			printf("Number of thread = %d  Number of threads = %d\n", omp_get_thread_num(), omp_get_num_threads());
		}
	}

	printf("\n");
#pragma omp parallel num_threads(4)
	{
#pragma omp for schedule(dynamic, 3)
		for (int i = 0; i < 12; i++) {
			c[i] = a[i] + b[i];
			printf("C[%d] = %d\n", i, c[i]);
			printf("Number of thread = %d  Number of threads = %d\n", omp_get_thread_num(), omp_get_num_threads());
		}
	}
}