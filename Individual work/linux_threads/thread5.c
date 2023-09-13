#include <stdio.h>
#include <pthread.h>

typedef struct{
	int x;
	char y[10];
	float z;
}xyz;

void* f(void* a){
	printf("F: %d\n", ((xyz*)a)->x);
	return NULL;
}
int main(int argc, char** argv)
{
	int i;
	xyz k[10];
	pthread_t t[10];
	for(i = 0; i < 10; i++)
	{
		k[i].x = i;
		k[i].y[0] = i;
		k[i].z = (float)i;
		pthread_create(&t[i], NULL, f, &k[i]);
	}
	for(i = 0; i < 10; i++)
		pthread_join(t[i], NULL);
	return 0;
}
