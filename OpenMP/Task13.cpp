#include <omp.h>
#include <iostream>
#include <stdio.h>


#define N 30

int main() {
    omp_set_num_threads(8);
    int a[N] = { 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1 };
    int result = 0;
#pragma omp parallel for reduction(+:result)
    for (int i = 0; i < N; i++) {
        if (a[i] == 1) {
            result = result + pow(2, N - i - 1);
        }
    }
    printf("Number = %d", result);
}