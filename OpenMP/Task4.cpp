#include <omp.h>
#include <iostream>
#include <stdio.h>


int main()
{
	int a[] = {1, 5, -2, 0, -1, 3, 8, 4, 5, 2};
	int b[] = { 6, 8, -2, 0, 5, 3, 2, 4, 1, 7};
	

	omp_set_num_threads(2);
#pragma omp parallel
	{
		int thread_num = omp_get_thread_num();
		if (thread_num == 0) {
			int min = a[0];
			for (int i = 0; i < 10; i++) {
				if (a[i] < min) {
					min = a[i];
				}
			}
			printf("min = %d", min);
		}
		if (thread_num == 1) {
			int max = b[0];
			for (int i = 0; i < 10; i++) {
				if (b[i] > max) {
					max = b[i];
				}
			}
			printf("max = %d", max);
		}
	}
}