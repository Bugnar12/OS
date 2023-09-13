#include <stdio.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t m; ///init variable mutex
pthread_cond_t c; ///init cond. variable

void* fa(void* a)
{
	int i;

	for(i = 0; i < 10; i++)
	{
		printf("A%d\n", i);
		pthread_mutex_lock(&m);
		pthread_cond_signal(&c); ///cond. var. sending a signal
		pthread_mutex_unlock(&m);
	}
	return NULL; ///important to always return null from a void* function
}

void* fb(void* b)
{
	pthread_mutex_lock(&m);
	pthread_cond_wait(&c, &m);  ///cond. var. waiting
	pthread_mutex_unlock(&m);
	printf("B\n");
	return NULL;
}

int main(int argc, char** argv)
{
	int i;
	pthread_t t[2];
	pthread_mutex_init(&m, NULL); ///initializing the mutex
	pthread_cond_init(&c, NULL); ///initializing the var. cond.
	pthread_create(&t[0], NULL, fa, NULL);
	pthread_create(&t[1], NULL, fb, NULL);
	for(i = 0; i < 2; i++)
		pthread_join(t[i], NULL);

	pthread_mutex_destroy(&m); ///destroy the mutex
	pthread_cond_destroy(&c); ///destroy the cond. var.
	
	return 0;

}

