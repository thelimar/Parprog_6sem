#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* HelloWorld(void* rank)
{
	printf("Hello world! Thread %d.\n", *(int*) rank);
	return NULL;
}


int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Enter number of threads\n");
		return -1;
	}
	
	int n_threads = atoi(argv[1]);
	
	pthread_t threads[n_threads];
	int ranks[n_threads];
	
	for (int i = 0; i < n_threads; i++)
	{
		ranks[i] = i;
		pthread_create(&threads[i], NULL, HelloWorld, &ranks[i]);
	}
	
	for  (int i = 0; i < n_threads; i++)
	{
		pthread_join(threads[i], NULL);
	}
	
	return 0;
}