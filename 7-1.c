#include<stdio.h> 
#include<string.h> 
#include<pthread.h> 
#include<stdlib.h> 
#include<unistd.h> 


#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES;

pthread_mutex_t mtx;

int decrease_count(int count)
{
	pthread_mutex_lock(&mtx);

	if(available_resources < count)
	{
		pthread_mutex_unlock(&mtx);
		return -1;
	}
	else
		available_resources -= count;
	printf("Got %d resources %d remaining\n", count, available_resources);
	pthread_mutex_unlock(&mtx);
	
	return 0;
}

int increase_count(int count)
{
	pthread_mutex_lock(&mtx);
	available_resources += count;
	printf("Released %d resources %d remaining\n", count, available_resources);
	pthread_mutex_unlock(&mtx);
	return 0;

}

void *fct(void *arg)
{
	int *res_folosite = (int*) arg;
	while(available_resources < *res_folosite)
		; //asteapta sa se elibereze

	if(available_resources >= *res_folosite)
		decrease_count(*res_folosite);
	
	increase_count(*res_folosite);

	return NULL;
}

int main()
{
	int n = 5;
	pthread_t threads[n];
	int resurse[] = {4, 3, 4, 2, 3};


	pthread_mutex_init(&mtx, NULL);

	for (int i = 0; i < n; ++i)
	{
		pthread_create(&threads[i], NULL, fct, &resurse[i]);
	}

	for (int i = 0; i < n; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&mtx);

	return 0;
}