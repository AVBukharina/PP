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

    const int n = 8;
    const int m = 8;

    int b[n / 2][m];
    int c[n / 2][m];

    MPI_Datatype newType;

    MPI_Type_vector(n / 2, n, n * 2, MPI_INT, &newType);
    MPI_Type_commit(&newType);

    if (rank == 0) {
        int a[n][m] = {
                {1, 1, 1, 1, 2, 2, 2, 2},
                {2, 2, 2, 2, 3, 3, 3, 3},
                {3, 3, 3, 3, 4, 4, 4, 4},
                {4, 4, 4, 4, 5, 5, 5, 5},
                {5, 5, 5, 5, 6, 6, 6, 6},
                {6, 6, 6, 6, 7, 7, 7, 7},
                {7, 7, 7, 7, 8, 8, 8, 8},
                {8, 8, 8, 8, 9, 9, 9, 9}
        };

        cout << "Initial Matrix: " << endl;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << a[i][j] << " ";
            }
            cout << endl;
        }

        for (int i = 0; i < 2; i++) {
            MPI_Send(&a[i][0], 1, newType, i + 1, 1, MPI_COMM_WORLD);
        }

    }

    if (rank == 1) {
        MPI_Status firstStatus;
        int firstSize;

        MPI_Probe(0, 1, MPI_COMM_WORLD, &firstStatus);
        MPI_Get_count(&firstStatus, MPI_INT, &firstSize);

        int* firstArray = new int[firstSize];
        MPI_Recv(firstArray, firstSize, MPI_INT, 0, 1, MPI_COMM_WORLD, &firstStatus);

        int count = 0;
        for (int i = 0; i < n / 2; i++) {
            for (int j = 0; j < n; j++) {
                b[i][j] = firstArray[count];
                count++;
            }
        }
        cout << "Uneven Matrix: " << endl;

        for (int i = 0; i < n / 2; i++) {
            for (int j = 0; j < n; j++) {
                cout << b[i][j] << " ";
            }
            cout << endl;
        }


    }

    if (rank == 2) {
        MPI_Status secondStatus;
        int secondSize;

        MPI_Probe(0, 1, MPI_COMM_WORLD, &secondStatus);
        MPI_Get_count(&secondStatus, MPI_INT, &secondSize);

        int* secondArray = new int[secondSize];
        MPI_Recv(secondArray, secondSize, MPI_INT, 0, 1, MPI_COMM_WORLD, &secondStatus);

        int count = 0;
        cout << "Even Matrix: " << endl;
        for (int i = 0; i < n / 2; i++) {
            for (int j = 0; j < n; j++) {
                c[i][j] = secondArray[count];
                count++;
                cout << c[i][j] << " ";
            }
            cout << endl;
        }
    }

    MPI_Finalize();
}
