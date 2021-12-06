#include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <math.h>

using namespace std;

int main(int argc, char** argv) {

    int rank;
    int size;

    const int n = 20;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    int sum = 0;
    int globalSum;

    int сount = n / size;

    int* sentBuffer = new int[n];
    int* receivedBuffer = new int[сount];

    for (int i = 0; i < n; i++) {
        sentBuffer[i] = i + 1;
    }

    MPI_Scatter(sentBuffer, сount, MPI_INT, receivedBuffer, сount, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < сount; i++) {
        sum += abs(receivedBuffer[i]);
    }

    cout << "Sum on procces " << rank << " = " << sum << endl;

    MPI_Reduce(&sum, &globalSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Sum = " << globalSum << endl;
    }

    MPI_Finalize();
}