#include <stdio.h>
#include "mpi.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	int size, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 1)
	{
		int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		for (int i = 0; i < size; i++) {
			if (i != 1) {
				MPI_Send(a, 10, MPI_INT, i, 1, MPI_COMM_WORLD);
			}
		}
	}
	else
	{
		int count;
		MPI_Status status;
		MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_INT, &count);
		int* arr = new int[count];
		MPI_Recv(arr, count, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

		cout << "Process " << rank << ": ";
		for (int i = 0; i < count; i++) {
			cout  << arr[i] << " ";
		}
	}
	MPI_Finalize();
}
