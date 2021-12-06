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


    int firstBuffer[n];
    int secondBuffer[n];

    int firstMatrix[n][m] =
    {
            {3,-1,0,2,4,3,1,4},
            {3,-1,0,2,4,3,-2,4},
            {3,-1,-1,0,4,0,2,-4},
            {-3,1,-1,0,4,0,-2,4},
            {3,-1,0,2,4,3,1,4},
            {2,-1,1,2,4,3,-3,4},
            {3,-1,3,0,2,0,3,-4},
            {-3,1,-3,0,2,2,-3,4}
    };

    int secondMatrix[n][m] =
    {
            {1,2,3,4,3,2,1,4},
            {1,4,1,4,1,4,1,4},
            {0,2,1,0,2,1,2,0},
            {-3,1,-1,0,4,0,-2,4},
            {3,-1,0,2,4,3,1,4},
            {2,-1,1,2,4,3,-3,4},
            {3,-1,3,0,2,0,3,-4},
            {-3,1,-3,0,2,2,-3,4}
    };

    int result[n][m];
    int resultBuffer[n];

    MPI_Scatter(firstMatrix, n, MPI_INT, firstBuffer, m, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(secondMatrix, n, MPI_INT, secondBuffer, m, MPI_INT, 0, MPI_COMM_WORLD);


    for (int i = 0; i < n; i++) {
        resultBuffer[i] = firstBuffer[i] * secondBuffer[i];
    }

    MPI_Gather(resultBuffer, n, MPI_INT, result, m, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Result: " << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << result[i][j] << " ";
            }
            cout << endl;
        }
    }

    MPI_Finalize();
}
