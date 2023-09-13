#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int n = 0;
pthread_mutex_t m[3];
pthread_mutex_t print_mutex;
void* f(void* p){
	int id = (int)p;
	pthread_mutex_lock(&m[id]);
	n += id;
	pthread_mutex_lock(&print_mutex);
	printf("%d ", n);
	fflush(stdout);
	pthread_mutex_unlock(&print_mutex);
	pthread_mutex_unlock(&m[(id+1) % 3]);
	return NULL;
}
int main()
{
	int i;
	pthread_t t[3];
	for(i = 0; i < 3; i++)
		pthread_mutex_init(&m[i], NULL);

	pthread_mutex_init(&print_mutex, NULL);

	for(i = 0; i < 3; i++){
		pthread_create(&t[i], NULL, f, (void*)i);
	}
		
	sleep(1);

	for(i=0; i < 3; i++)
		pthread_join(t[i], NULL);

	pthread_mutex_destroy(&print_mutex);

	for(i=0; i<3; i++)
		pthread_mutex_destroy(&m[i]);
	
	return 0;
}
