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
		}
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			printf("% d", d[i][j]);
		}
		printf("\n");
	}



#pragma omp parallel sections
		{
#pragma omp section
			{
				int thread_num = omp_get_thread_num();
				int s = 0;
				for (int i = 0; i < 6; i++) {
					for (int j = 0; j < 8; j++) {
						s += d[i][j];
					}
				}
				s = s / (6 * 8);
				printf("Number of thread = %d. Arithmetic mean = %d \n", thread_num, s);
			}
#pragma omp section
			{
				int thread_num = omp_get_thread_num();
				int min = d[0][0];
				int max = d[0][0];
				for (int i = 0; i < 6; i++) {
					for (int j = 0; j < 8; j++) {
						if (d[i][j] < min) {
							min = d[i][j];
						}
						if (d[i][j] > max) {
							max = d[i][j];
						}
					}
				}
				printf("Number of thread = %d. Min = %d. Max = %d \n", thread_num, min, max);
			}
#pragma omp section
			{
				int thread_num = omp_get_thread_num();
				int count = 0;
				for (int i = 0; i < 6; i++) {
					for (int j = 0; j < 8; j++) {
						if (d[i][j] % 3 == 0) {
							count++;
						}
					}
				}
				printf("Number of thread = %d. The numbers are multiples of 3 = %d \n", thread_num, count);
			}
		}
	}