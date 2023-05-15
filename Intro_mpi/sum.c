#include <mpi.h>
#include <stdio.h> 
#include <stdlib.h>

void helper(int rank, int commsize, int N)
{
	double sum = 0.0;
	int steps = N / (commsize - 1);
	int start = steps * (rank - 1) + 1;
	
	if (rank == commsize-1)
	{
		steps += N % (commsize-1);
	}
	
	for (int i = start, end = start + steps; i < end; i++)
	{
		sum += 1.0/i;
	}
	
	MPI_Send(&sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
}

double leader(int commsize)
{
	double total_sum = 0.0;
	
	for (int i = 1; i < commsize; i++)
	{
		MPI_Status status;
		double current_sum = 0.0;
		
		MPI_Recv(&current_sum, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
		
		total_sum += current_sum;
	}
	
	return total_sum;
	
}

int main(int argc, char* argv[])
{
	int commsize, my_rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &commsize);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	
	if (argc >= 2)
	{
		if (my_rank == 0)
		{
			printf("Sum is: %lf\n", leader(commsize));
		}
		else
		{
			helper(my_rank, commsize, atoi(argv[1]));
		}
	}
	else if (my_rank == 0)
	{
	printf("Enter N\n");
	}
		
	MPI_Finalize();
	
	return 0;
}