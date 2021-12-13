#include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <math.h>

using namespace std;

int main(int argc, char** argv) {

    int rank;
    int size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        int array[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

        int block = (12 / size) + 1;

        cout << "From procces " << rank << endl;

        for (int i = 0; i < block; i++) {
            cout << array[i] << " ";
        }
        cout << endl;


        for (int i = 1; i < size; i++) {

            int start = i * (12 / size) + i;

            if (12 - start <= block) {
                block = 12 - start;
            }

            if (block < 0) {
                MPI_Send(array + start, 0, MPI_INT, i, 1, MPI_COMM_WORLD);
            }
            else {
                MPI_Send(array + start, block, MPI_INT, i, 1, MPI_COMM_WORLD);
            }
        }

    }
    else {

        int count;
        MPI_Status status;

        MPI_Probe(MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);

        int* newArray = new int[count];

        MPI_Recv(newArray, count, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

        cout << "Accepted the message process: " << rank << endl;
        for (int i = 0; i < count; i++) {
            cout << newArray[i] << " ";
        }
        cout << endl;
    }

    MPI_Finalize();
}
