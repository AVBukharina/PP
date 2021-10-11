#include <omp.h>
#include <iostream>
#include <stdio.h>


int main()
{
	int a = 3;
	int b = 5;
#pragma omp parallel private (a) firstprivate (b) num_threads(2)
	{
		a = 8;
		int thread_num = omp_get_thread_num();
		printf("Number of thread = %d. Before action: a = %d, b = %d\n", thread_num, a, b);
		a += thread_num;
		b += thread_num;
		printf("Number of thread = %d. After action: a = %d, b = %d\n", thread_num, a, b);
	}
	a = 3;
	b = 5;
	printf("\n");
#pragma omp parallel shared (a) private (b) num_threads(4)
	{
		b = 5;
		int thread_num = omp_get_thread_num();
		printf("Number of thread = %d. Before action: a = %d, b = %d\n", thread_num, a, b);
		a -= thread_num;
		b -= thread_num;
		printf("Number of thread = %d. After action: a = %d, b = %d\n", thread_num, a, b);
	}
}