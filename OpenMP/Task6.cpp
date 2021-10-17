#include <omp.h>
#include <iostream>
#include <stdio.h>


int main()
{
	int a[10] = { 1, 2, 6, 4, 2, 6, 5, 4, 1, 2 };
	int b[10] = { 4, 2, 3, 6, 5, 1, 3, 4, 5, 5 };

	int sum_a = 0, sum_b = 0;
#pragma omp parallel for reduction(+: sum_a) reduction(+: sum_b)
	for (int i = 0; i < 10; i++) {
		sum_a += a[i];
		sum_b += b[i];
	}
	printf("Arithmetic mean A = %d\n Arithmetic mean B = %d", sum_a/10 , sum_b/10 );
}