#include <iostream>
#include <mpi.h>
#include <stdio.h>
#include <math.h>

using namespace std;

struct LinesType
{
    int firstLine[8];
    int secondLine[8];
};

int main(int argc, char** argv) {

    int rank;
    int size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int n = 8;
    const int m = 8;

    struct LinesType linesType;
    int block[2] = { n, n };

    MPI_Datatype types[2] = { MPI_INT, MPI_INT };
    MPI_Aint adr[2];

    adr[0] = offsetof(struct LinesType, firstLine);
    adr[1] = offsetof(struct LinesType, secondLine);

    MPI_Datatype newType;

    MPI_Type_create_struct(2, block, adr, types, &newType);
    MPI_Type_commit(&newType);

    int a[n][m];


    if (rank == 4) {
        cout << "Matrix a: " << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = i;
                cout << a[i][j] << " ";
            }
            cout << endl;
        }

        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < n; j++) {
                linesType.firstLine[j] = a[i][j];
                linesType.secondLine[j] = a[i + 4][j];
            }
            MPI_Send(&linesType, 1, newType, i, 1, MPI_COMM_WORLD);
        }
    }

    else {
        MPI_Status status;

        MPI_Recv(&linesType, 1, newType, 4, 1, MPI_COMM_WORLD, &status);
        int d[2][n];
        for (int j = 0; j < n; j++) {
            d[0][j] = linesType.firstLine[j];
            d[1][j] = linesType.secondLine[j];
        }


        cout << "Matrix d on procces: " << rank << endl;

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 8; j++) {
                cout << d[i][j] << " ";
            }
            cout << endl;
        }
    }

    MPI_Finalize();
}