#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5
#define NUM_NUMBERS 1000
#define DISPLAY_INTERVAL 10

pthread_mutex_t mutex;
pthread_cond_t cond;

int numbers[NUM_NUMBERS];
int count = 0;

void *generate_numbers(void *thread_id) {
	long tid = (long)thread_id;
    int start = tid * (NUM_NUMBERS / NUM_THREADS);
    int end = start + (NUM_NUMBERS / NUM_THREADS);

    for (int i = start; i < end; i++) {
        int num = rand() % 1000;

        pthread_mutex_lock(&mutex);

        int j;
        for (j = count - 1; j >= 0; j--) {
            if (num >= numbers[j])
                break;

            numbers[j + 1] = numbers[j];
        }

        numbers[j + 1] = num;
        count++;

        if (count % DISPLAY_INTERVAL == 0) {
            printf("Current vector: ");
            for (int k = 0; k < count; k++) {
                printf("%d ", numbers[k]);
            }
            printf("\n");
        }

        pthread_mutex_unlock(&mutex);

        usleep(10000); // Sleep for 10 milliseconds
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    void *status;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (long t = 0; t < NUM_THREADS; t++) {
        pthread_create(&threads[t], &attr, generate_numbers, (void *)t);
    }

    for (long t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], &status);
    }

    printf("Final vector: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    pthread_exit(NULL);

    return 0;
}

