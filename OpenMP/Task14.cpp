#include <omp.h>
#include <iostream>
#include <stdio.h>


#define N 210

int main() {
    omp_set_num_threads(4);
    int result = 0;
    int a = 1;
#pragma omp parallel for shared(a) reduction(+:result)
    for (int i = 0; i < N; i++) {
#pragma omp critical
        {
            result = result + a;
            a = a + 2;
        }
    }
    printf("Number = %d", result);
}