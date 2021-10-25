#include <omp.h>
#include <iostream>
#include <stdio.h>

#define N 30

int main() {
	int a[N];
	srand(time(NULL));
	for (int i = 0; i < N; i++) {
		a[i] = rand();
		printf("%d  ", a[i]);
	}

	int count = 0;
#pragma omp parallel for shared(count)
	for (int i = 0; i < N; i++) {
		if (a[i] % 9 == 0) {
#pragma omp atomic
			count++;
		}
	}
	printf("\nCount = %d", count);
}