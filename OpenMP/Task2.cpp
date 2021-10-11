#include <omp.h>
#include <iostream>
#include <stdio.h>

int main()
{
	int a = 3;
#pragma omp parallel if (a>1) num_threads(a)
	{
		printf("Hello world! Number of thread = %d. Number of threads = %d\n", omp_get_thread_num(), omp_get_num_threads());
	}
	printf("\n");
	int b = 1;
#pragma omp parallel if (b>1) num_threads(b)
	{
		printf("Hello world! Number of thread = %d. Number of threads = %d\n", omp_get_thread_num(), omp_get_num_threads());
	}
}