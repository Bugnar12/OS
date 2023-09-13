#include <stdio.h>
#include <pthread.h>

pthread_mutex_t m;
int n = 0;

void* f(void* a)
{
	int i;
	for(i = 0; i < 1000 * 1000; i++)
	{
		pthread_mutex_lock(&m);
		n++;
		pthread_mutex_unlock(&m);
	}
	return NULL;
}

int main(int argc, char** argv)
{
	int i;
	pthread_t t[10];
	pthread_mutex_init(&m, NULL); ///initialization of the mutex
	for(i = 0; i < 10; i++)
		pthread_create(&t[i], NULL, f, NULL);
	for(i = 0; i < 10; i++)
		pthread_join(t[i], NULL);

	pthread_mutex_destroy(&m); ///destruction of the mutex
	printf("%d\n", n);

	return 0;
}
