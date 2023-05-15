#include <mpi.h>
#include <stdio.h> 
#include <stdlib.h>

void leader(int commsize)
{
	int message = 0;
	printf("Current message is %d. Current process rank is 0.\n", message);
	message++;
	
	int to = 1;
	int from = commsize - 1;
	if (commsize == 1)
	{
		from = 0;
		to = 0;
	}
	
	MPI_Status status;
	MPI_Send(&message, 1, MPI_INT, to, 0, MPI_COMM_WORLD);
	MPI_Recv(&message, 1, MPI_INT, from, 0, MPI_COMM_WORLD, &status);

	printf("Current message is %d. Current process rank is 0.\n", message);
	
	return;
}


void chain_send(int rank, int commsize)
{
	if (rank == 0)
	{
		leader(commsize);
		return;
	}
	
	int from = rank - 1;
	int to   = rank == commsize - 1 ? 0 : rank + 1;
	
	int message = 0;
	
	MPI_Status status;
	MPI_Recv(&message, 1, MPI_INT, from, 0, MPI_COMM_WORLD, &status);
	printf("Current message is %d. Current process rank is %d.\n", message, rank);
	message++;
	MPI_Send(&message, 1, MPI_INT, to, 0, MPI_COMM_WORLD);
	
	return;
}

int main(int argc, char* argv[])
{
	setbuf(stdout, NULL);

	int commsize, my_rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &commsize);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	chain_send(my_rank, commsize);
	
	MPI_Finalize();
	
	return 0;
}