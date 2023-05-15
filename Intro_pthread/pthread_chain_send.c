#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n_threads;
int message = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void* ChainSend(void* rank)
{
    pthread_mutex_lock(&mutex);
    int cur_msg = message;
	message++;
    pthread_mutex_unlock(&mutex);
	
	printf ("Thread is: %d. Current message is %d\n", *(int *)(rank), message);
	
	return NULL;
}


int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Enter number of threads\n");
		return -1;
	}
	
	n_threads = atoi(argv[1]);
	
	pthread_t threads[n_threads];
	int ranks[n_threads];
	
	pthread_mutex_unlock(&mutex);
	
	for (int i = 0; i < n_threads; i++)
	{
		ranks[i] = i;
		pthread_create(&threads[i], NULL, ChainSend, &ranks[i]);
	}
	
	for  (int i = 0; i < n_threads; i++)
	{
		pthread_join(threads[i], NULL);
	}
	
	return 0;
}