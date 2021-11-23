#include "mpi.h"
#include <stdio.h>
#include <iostream>
using namespace std;


int main(int argc, char** argv) {
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0)
	{
		int N = 50;
		int* x = new int[50];
		int* y = new int[50];
		for (int i = 0; i < N; i++)
		{
			x[i] = i+1;
			y[i] = i;
		}
		cout << "x = { ";
		for (int i = 0; i < N; i++)
		{
			cout << x[i] << " ";
		}
		cout << " }" << "\n";
		cout << "y = { ";
		for (int i = 0; i < N; i++)
		{
			cout << y[i] << " ";
		}
		cout << " }" << "\n";
		int block = N / (size - 1) + (N / (size - 1)) % 2 + 2;
		for (int i = 1; i < size; i++)
		{
			int* arr = new int[block];
			int start = (i - 1) * (block);
			int end = i * (block);
			if (end > N) {
				end = N;
			}
			for (int j = start; j < end; j++)
			{
				arr[j - start] = x[j];
			}
			MPI_Send(arr, end - start, MPI_INT, i, 5, MPI_COMM_WORLD);
			for (int j = start; j < end; j++)
			{
				arr[j - start] = y[j];
			}
			MPI_Send(arr, end - start, MPI_INT, i, 6, MPI_COMM_WORLD);

		}
		for (int i = 1; i < size; i++)
		{
			int count;
			MPI_Status status;

			MPI_Probe(i, 7, MPI_COMM_WORLD, &status);
			MPI_Get_count(&status, MPI_INT, &count);
			int* arrX = new int[count];
			MPI_Recv(arrX, count, MPI_INT, i, 7, MPI_COMM_WORLD, &status);
			MPI_Probe(i, 8, MPI_COMM_WORLD, &status);
			MPI_Get_count(&status, MPI_INT, &count);
			int* arrY = new int[count];
			MPI_Recv(arrY, count, MPI_INT, i, 8, MPI_COMM_WORLD, &status);
			cout << "From process " << i << ": " << endl;
			cout << "x = { ";
			for (int j = 0; j < count; j++)
			{
				cout << arrX[j] << " ";
			}
			cout << " }" << "\n";
			cout << "y = { ";
			for (int j = 0; j < count; j++)
			{
				cout << arrY[j] << " ";
			}
			cout << " }" << "\n";
		}
	}
	else
	{
		int count;
		MPI_Status status;

		MPI_Probe(0, 5, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_INT, &count);
		int* arrX = new int[count];
		MPI_Recv(arrX, count, MPI_INT, 0, 5, MPI_COMM_WORLD, &status);

		MPI_Probe(0, 6, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_INT, &count);
		int* arrY = new int[count];
		MPI_Recv(arrY, count, MPI_INT, 0, 6, MPI_COMM_WORLD, &status);
		
		MPI_Send(arrY, count, MPI_INT, 0, 7, MPI_COMM_WORLD);
		MPI_Send(arrX, count, MPI_INT, 0, 8, MPI_COMM_WORLD);
	}

	MPI_Finalize();
}
