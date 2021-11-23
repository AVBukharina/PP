#include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <math.h>

using namespace std;

int main(int argc, char** argv) {

    int rank;
    int size;

    const int n = 2;
    const int m = 3;
    double c[n][m];
    double vector[n];
    

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {

        double a[m][n] =
        {
                {1, 2},
                {3, 4},
                {5, 6}
        };


        int num = ceil((double)m / (size - 1));

        printf("Procces: %d \n", rank);
        for (int i = 1; i < size; i++) {

            int start = (i - 1) * num;

            if (m - start <= num) {
                num = m - start;
            }
            start = (i - 1) * num;

            MPI_Send(&num, 1, MPI_INT, i, 2, MPI_COMM_WORLD);
            MPI_Send(&start, 1, MPI_INT, i, 4, MPI_COMM_WORLD);

            for (int j = start; j < start + num; j++) {
                MPI_Send(&a[j][0], n, MPI_DOUBLE, i, 11, MPI_COMM_WORLD);
            }

        }

        for (int i = 1; i < size; i++) {

            printf("Procces: %d \n", i);

            MPI_Status cStatus;
            MPI_Status status;
            MPI_Status numStatus;
            int start;
            int num;
            double vectorBuffer[n];

            MPI_Recv(&start, 1, MPI_INT, i, 5, MPI_COMM_WORLD, &status);
            MPI_Recv(&num, 1, MPI_INT, i, 7, MPI_COMM_WORLD, &numStatus);
            MPI_Recv(&vectorBuffer, n, MPI_DOUBLE, i, 12, MPI_COMM_WORLD, &cStatus);


            for (int j = start; j < start + num; j++) {

                for (int l = 0; l < n; l++) {
                    c[l][j] = vectorBuffer[l];
                    printf("c[%d][%d] : %.2f ", l, j, c[l][j]);
                }

                printf("\n");
            }

        }

        printf("\n");
    }

    else if (rank != 0) {
        int countOfElements;
        int start;
        MPI_Status aStatus;
        MPI_Status elemStatus;
        MPI_Status startStatus;

        MPI_Recv(&countOfElements, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &elemStatus);
        MPI_Recv(&start, 1, MPI_INT, MPI_ANY_SOURCE, 4, MPI_COMM_WORLD, &startStatus);

        double buffer_a[m][n];

        printf("Procces: %d \n", rank);
        for (int i = start; i < start + countOfElements; i++) {
            MPI_Recv(&buffer_a[i][0], n, MPI_DOUBLE, MPI_ANY_SOURCE, 11, MPI_COMM_WORLD, &aStatus);

            for (int j = 0; j < n; j++) {
                printf("a[%d][%d] : %.2f ", i, j, buffer_a[i][j]);
                vector[j] = buffer_a[i][j];
            }
            printf("\n");

            for (int j = 0; j < n; j++) {
                printf("vector[%d] : %.2f ", j, vector[j]);
            }

            printf("\n");

        }

        MPI_Send(&start, 1, MPI_INT, 0, 5, MPI_COMM_WORLD);
        MPI_Send(&countOfElements, 1, MPI_INT, 0, 7, MPI_COMM_WORLD);
        MPI_Send(&vector, n, MPI_DOUBLE, 0, 12, MPI_COMM_WORLD);

        printf("\n");
    }

    MPI_Finalize();
}
