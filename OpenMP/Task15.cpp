#include <omp.h>
#include <iostream>
#include <stdio.h>

#pragma warning(disable:4996)

int main()
{
    int i, j, p;
    int end;
    printf("Enter N: ");
    scanf("%d", &end);
#pragma omp parallel for
    for (i = 2; i <= end; i++)
    {
        p = 1;
        for (j = 2; j <= i / 2; j++)
        {
            if (i % j == 0)
            {
                p = 0;
                break;
            }
        }

        if (p == 1) {
            printf("%d, ", i);
        }
    }
}