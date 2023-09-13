#include <stdio.h>
#include <pthread.h>

int n = 0;

void* f(void* a)
{
	int i;
	for(i = 0; i < 1000 * 1000; i++)
		n++;
	return NULL;
}

int main(int argc, char** argv)
{
	int i;
	pthread_t t[10];

	for(i = 0; i < 10; i++)
		pthread_create(&t[i], NULL, f, NULL);

	for(i = 0; i < 10; i++)
		pthread_join(t[i], NULL);

	printf("%d\n", n);
	return 0;

}
