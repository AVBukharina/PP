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


    int localSum = 0;
    int globalSum = 0;
    int max = 0;

    int sentBuffer[n][m];
    int receivedBuffer[n];

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

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sentBuffer[i][j] = matrix[j][i];
        }
    }

    MPI_Scatter(sentBuffer, n, MPI_INT, receivedBuffer, m, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < n; i++) {
        localSum += abs(receivedBuffer[i]);
    }

    cout << "Sum on procces " << rank << " = " << localSum << endl;

    MPI_Reduce(&localSum, &max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Max " << max << endl;
    }

    MPI_Finalize();
}