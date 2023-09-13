#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* f(void* a)
{
	printf("F: %d\n", *(int*)a);
	free(a);
	return NULL;
}
int main(int argc, char** argv)
{
	int i, *p;
	pthread_t t[10];
	for(i = 0; i < 10; i++)
	{
		p = (int*)malloc(sizeof(int));
		*p = i;
		pthread_create(&t[i], NULL, f, p);
	}
	for(i = 0; i < 10; i++)
		pthread_join(t[i], NULL);
	
	return 0;
}
