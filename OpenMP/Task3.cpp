#include <omp.h>
#include <iostream>
#include <stdio.h>


int main()
{
	int a = 3;
	int b = 5;
	printf("Before action: a = %d, b = %d\n", a, b);
#pragma omp parallel private (a) firstprivate (b) num_threads(2)
	{
		a = 3;
		int thread_num = omp_get_thread_num();
		a += thread_num;
		b += thread_num;
		printf("Number of thread = %d. Inside action: a = %d, b = %d\n", thread_num, a, b);
	}
	printf("After action: a = %d, b = %d\n", a, b);
	printf("\n");
	printf("Before action: a = %d, b = %d\n", a, b);
#pragma omp parallel shared (a) private (b) num_threads(4)
	{
		b = 5;
		int thread_num = omp_get_thread_num();
		a -= thread_num;
		b -= thread_num;
		printf("Number of thread = %d. Inside action: a = %d, b = %d\n", thread_num, a, b);
	}
	printf("After action: a = %d, b = %d\n", a, b);
}
