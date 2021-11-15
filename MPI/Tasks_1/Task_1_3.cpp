#include "mpi.h"
#include <stdio.h>
#include <iostream>

int main(int argc, char** argv) {
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;
	if (rank == 0) {
		int a[10];
		printf("Array from process 0 to process 1: ");
		for (int i = 0; i < 10; i++) {
			a[i] = rand() % 10 + 1;
			printf("%d ", a[i]);
		}
		MPI_Send(&a, 10, MPI_INT, 1, 10, MPI_COMM_WORLD);
	}
	else {
		int a[10];
		MPI_Recv(a, 10, MPI_INT, 0, 10, MPI_COMM_WORLD, &status);
		printf("The resulting array of 0 processes: ");
		for (int i = 0; i < 10; i++) {
			printf("%d ", a[i]);
		}
	}
	MPI_Finalize;
}
