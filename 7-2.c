#include<stdio.h> 
#include<string.h> 
#include<pthread.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<semaphore.h>

#define N  5
int counter = 0;

pthread_mutex_t mtx;
sem_t sem;

void barrier_point()
{
	pthread_mutex_lock(&mtx);
	counter++;
	if(counter == N)
		sem_post(&sem);
	pthread_mutex_unlock(&mtx);
	sem_wait(&sem);
	sem_post(&sem);
s
}

void *tfun(void *v)
{
	int *tid = (int*) v;

	printf("%d reached the barrier \n", *tid);
	barrier_point();
	printf("%d passed the barrier \n", *tid);

	return NULL;
}


int main()
{
	sem_init(&sem, 0, 0);

	pthread_mutex_init(&mtx, NULL);

	pthread_t threads[N];

	int v[N];

	for (int i = 0; i < N; ++i)
	{
		v[i] = i;
		pthread_create(&threads[i], NULL, tfun, &v[i]);
	}

	for (int i = 0; i < N; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	sem_destroy(&sem);
	pthread_mutex_destroy(&mtx);


	return 0;
}