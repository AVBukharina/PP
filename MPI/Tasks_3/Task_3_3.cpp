#include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <math.h>

using namespace std;

int main(int argc, char** argv) {

    int rank;
    int size;

    const int n = 8;
    const int m = 8;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    int localResult = 0;
    int globalSum = 0;
    int max = 0;


    int sendCount = n / size;


    int receivedBuffer[n];
    int result[n];

    int matrix[n][m] =
    {
            {3,  -1, 0,  2, 2, 3, 1,  0},
            {2,  -1, 1,  1, 4, 3, -2, 1},
            {3,  -2, -1, 0, 0, 0, 2,  -3},
            {-2, 2,  -2, 2, 0, 2, -2, 1},
            {3,  -1, 0,  2, 2, 3, 1,  0},
            {2,  -1, 1,  1, 4, 3, -2, 1},
            {3,  -2, -1, 0, 0, 0, 2,  -3},
            {-2, 2,  -2, 2, 0, 2, -2, 1}
    };

    int vector[n] = { 1, 2, 3, 4, 4, 3, 2, 1 };


    MPI_Scatter(matrix, n, MPI_INT, receivedBuffer, m, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Bcast(vector, n, MPI_INT, 0, MPI_COMM_WORLD);


    for (int i = 0; i < n; i++) {
        localResult += receivedBuffer[i] * vector[i];
    }


    cout << "Result on procces " << rank << " = " << localResult << endl;


    MPI_Gather(&localResult, 1, MPI_INT, result, 1, MPI_INT, 0, MPI_COMM_WORLD);


    if (rank == 0) {
        cout << "Result: " << endl;
        for (int i = 0; i < n; i++) {
            cout << result[i] << " ";
        }
        cout << endl;
    }

    MPI_Finalize();
}
