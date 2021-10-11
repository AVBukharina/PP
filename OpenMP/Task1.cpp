#include <omp.h>
#include <iostream>
#include <stdio.h>
int main() {
	
#pragma omp parallel num_threads(8)
	{
		printf("Hello world! Number of thread = %d. Number of threads = %d\n", omp_get_thread_num(), omp_get_num_threads());
	}
}