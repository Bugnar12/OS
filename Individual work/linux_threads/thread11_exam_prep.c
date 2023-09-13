#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 1000
#define THREAD_COUNT 5
#define PRINT_INTERVAL 10

int array[ARRAY_SIZE];
pthread_mutex_t mutex;

typedef struct _ThreadParam {
    int threadId;
} ThreadParam;

void* generateNumbers(void* param) {
    ThreadParam* threadParam = (ThreadParam*)param;
    int threadId = threadParam->threadId;

    for (int i = 0; i < ARRAY_SIZE / THREAD_COUNT; i++) {
        int number = rand() % 1000;
        int insertIndex = threadId * (ARRAY_SIZE / THREAD_COUNT) + i;

        pthread_mutex_lock(&mutex);

        int j = insertIndex - 1;
        while (j >= 0 && array[j] > number) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = number;

        pthread_mutex_unlock(&mutex);

        if (insertIndex % PRINT_INTERVAL == 0) {
            printf("Thread %d: ", threadId);
            for (int k = 0; k <= insertIndex; k++) {
                printf("%d ", array[k]);
            }
            printf("\n");
        }
    }

    return NULL;
}

int main() {
    pthread_t threads[THREAD_COUNT];
    ThreadParam threadParams[THREAD_COUNT];

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < THREAD_COUNT; i++) {
        threadParams[i].threadId = i;
        pthread_create(&threads[i], NULL, generateNumbers, (void*)&threadParams[i]);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nFinal sorted array:\n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
        if ((i + 1) % PRINT_INTERVAL == 0) {
            printf("\n");
        }
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}

