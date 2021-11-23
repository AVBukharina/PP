#include "mpi.h"
#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;


int main(int argc, char** argv) {

    int rank;
    int size;

    const int n = 4;
    int  a[n][n];
    int b[n][n];
    int c[n][n];

    MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        int number = 1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = number;
                b[i][j] = number;
                number++;
            }
        }

        int block = ceil((double)n / (size - 1));


        for (int i = 1; i < size; i++) {
            int start = (i - 1) * block;

            if (n - start <= block) {
                block = n - start;
            }

            MPI_Send(&block, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
            MPI_Send(&start, 1, MPI_INT, i, 2, MPI_COMM_WORLD);


            for (int j = start; j < start + block; j++) {
                MPI_Send(&a[j][0], n, MPI_INT, i, 11, MPI_COMM_WORLD);
                MPI_Send(&b[j][0], n, MPI_INT, i, 12, MPI_COMM_WORLD);

            }

            int arrC[n][n];
            MPI_Status cStatus;

            for (int j = start; j < start + block; j++) {
                MPI_Recv(&arrC[j], n, MPI_INT, i, 13, MPI_COMM_WORLD, &cStatus);

                for (int k = 0; k < n; k++) {
                    cout << "Array c[" << j << "][" << k << "] = " << arrC[j][k] << "; ";
                }
                cout << endl;
            }
            
        }

    }
    else if (rank != 0) {

        int countOfElements;
        int start;

        MPI_Status aStatus;
        MPI_Status bStatus;

        MPI_Status blockStatus;
        MPI_Status startStatus;

        MPI_Recv(&countOfElements, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &blockStatus);
        MPI_Recv(&start, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &startStatus);

        int  arrA[n][n];
        int  arrB[n][n];

        cout << "Procces " << rank << endl;

        for (int i = start; i < start + countOfElements; i++) {

            MPI_Recv(&arrA[i], n, MPI_INT, MPI_ANY_SOURCE, 11, MPI_COMM_WORLD, &aStatus);
            MPI_Recv(&arrB[i], n, MPI_INT, MPI_ANY_SOURCE, 12, MPI_COMM_WORLD, &bStatus);

            for (int j = 0; j < n; j++) {
                cout << "Array a[" << i << "][" << j << "] = " << arrA[i][j] << "; ";

            }
            cout << endl;

            for (int j = 0; j < n; j++) {
                cout << "Array b[" << i << "][" << j << "] = " << arrB[i][j] << "; ";
            }

            cout << endl;

            for (int j = 0; j < n; j++) {
                c[i][j] = arrA[i][j] * arrB[i][j];
            }

            MPI_Send(&c[i][0], n, MPI_INT, 0, 13, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
}