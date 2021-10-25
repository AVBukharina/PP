#include <omp.h>
#include <iostream>
#include <stdio.h>


#define N 30

int main() {
	int a[N];
	srand(time(NULL));
	for (int i = 0; i < N; i++) {
		a[i] = rand();
		printf("%d ", a[i]);
	}
	int max = 0;
#pragma omp parallel for shared(max)
	for (int i = 0; i < N; i++) {
		if (a[i] % 7 == 0 && max < a[i]) {
#pragma omp critical
			max = a[i];
		}
	}
	printf("\nMax = %d", max);
}