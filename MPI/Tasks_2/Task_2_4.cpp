#include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <math.h>

using namespace std;

int main(int argc, char** argv) {

    int rank;
    int size;

    const int n = 4;
    double a[n][n];
    double b[n][n];
    double c[n][n];

    int err = MPI_Init(&argc, &argv);

    err = MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    err = MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = 1.0;
                b[i][j] = 1.1;
            }
        }

        int block = ceil((double)n / (size - 1));

        cout << "Procces " << rank << endl;

        for (int i = 1; i < size; i++) {

            int start = (i - 1) * block;

            if (n - start <= block) {
                block = n - start;
            }
            start = (i - 1) * block;

            MPI_Send(&b[0][0], n * n, MPI_INT, i, 2, MPI_COMM_WORLD);

            for (int j = start; j < start + block; j++) {
                MPI_Send(&a[j], n, MPI_INT, i, 1, MPI_COMM_WORLD);
            }
        }
        for (int i = 1; i < size; i++) {
            int* arrC = new int[n];
            MPI_Status cStatus;

            for (int j = 0; j < n; j++) {
                arrC[j] = 0;
            }
            MPI_Recv(arrC, n, MPI_INT, i, 11, MPI_COMM_WORLD, &cStatus);

            for (int j = 0; j < n; j++) {
                cout << "c : " << arrC[j];
            }
            cout << endl;
        }

    }
    else if (rank != 0) {

        MPI_Status aStatus;
        MPI_Status bStatus;

        int* arrA = new int[n];
        int arrB[n][n];
        int multiplication[n];

        cout << "Procces: " << rank << endl;

        MPI_Recv(arrA, n, MPI_INT, 0, 1, MPI_COMM_WORLD, &aStatus);
        MPI_Recv(&arrB, n * n, MPI_INT, 0, 2, MPI_COMM_WORLD, &bStatus);

        for (int j = 1; j < n; j++) {
            cout << "a[" << j << "] : " << arrA[j] << " ";
        }
        cout << endl;

        for (int j = 1; j < n; j++) {
            for (int i = 0; i < n; i++) {
                cout << "b[" << j << "][" << i << "] : " << arrB[j][i] << " ";
            }
            cout << endl;
        }

        for (int i = 1; i < n; i++) {
            multiplication[i] = 0;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                multiplication[i] += arrA[j] * arrB[j][i];
            }
            cout << "multi[" << i << "] : " << multiplication[i] << " ";
        }
        cout << endl;

        MPI_Send(&multiplication, n, MPI_INT, 0, 11, MPI_COMM_WORLD);

    }
    MPI_Finalize();
}

