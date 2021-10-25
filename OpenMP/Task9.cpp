#include <omp.h>
#include <iostream>
#include <stdio.h>


int main()
{
	int d[6][8];
	srand(time(NULL));
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			d[i][j] = rand();
			printf("%d   ", d[i][j]);
		}
		printf("\n");
	}

	int min = d[0][0];
	int max = d[0][0];
#pragma omp parallel num_threads(5)
	{
		int myid = omp_get_thread_num();

#pragma omp for
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 8; j++) {
#pragma omp critical
	{
		if (d[i][j] < min) {
			min = d[i][j];
		}
	}
#pragma omp critical
	{
		if (d[i][j] > max) {
			max = d[i][j];
		}
	}
			}
		}
		printf("Number of thread = %d Min = %d Max = %d \n", myid, min, max);
	}
}