#include <stdio.h>
#include <pthread.h>

pthread_mutex_t a, b;
int n = 0;

void* fa(void* a)
{
	pthread_mutex_lock(&a);
	n++;
	pthread_mutex_unlock(&a);
}

void* fb(void* b)
{
	pthread_mutex_lock(&b);
	n++;
	pthread_mutex_unlock(&b);
}
