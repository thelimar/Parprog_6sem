#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n_threads;
int N;

void* Sum(void* rank)
{
	double sum = 0.0;
	int steps = N / n_threads;
	int start = steps * (*(int*)(rank)) + 1;
	
	if (*(int*) (rank) + 1 == n_threads)
	{
		steps += N % n_threads;
	}
	
	for (int i = start, end = start + steps; i < end; i++)
	{
		sum += 1.0 / i;
	}
	
	double* out_sum = (double*) malloc(sizeof(double));
	*out_sum = sum;
	
	return out_sum; 
	
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("Enter number of threads and N\n");
		return 0;
	}
	
	pthread_t threads[n_threads];
	int ranks[n_threads];
	
	n_threads = atoi(argv[1]);
	N = atoi(argv[2]);
	double total_sum = 0.0;
	
	for (int i = 0; i < n_threads; i++)
	{
		ranks[i] = i;
		pthread_create(&threads[i], NULL, &Sum, &ranks[i]);
	}
	
	
	
	for  (int i = 0; i < n_threads; i++)
	{
		double* sum = NULL;
		pthread_join(threads[i], (void **) (&sum));
		total_sum += *sum;
		free(sum);
	}
	
	printf("Total sum is: %lf\n", total_sum);
	
	return 0;
}