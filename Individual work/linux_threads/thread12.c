#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_NUMBERS 100
#define VECTOR_SIZE 100

pthread_mutex_t mutex;
pthread_barrier_t barrier;
pthread_cond_t cond;
int threads_ready = 0;

int L[VECTOR_SIZE];
int U[VECTOR_SIZE];
int L_size = 0;
int U_size = 0;
int S = 0;
int firstThread = 1;

typedef struct _ThreadParam {
    int number;
} ThreadParam;

void* processNumber(void* param) {
    ThreadParam* threadParam = (ThreadParam*)param;
    int number = threadParam->number;

    pthread_mutex_lock(&mutex);
    threads_ready++;
    if (threads_ready == MAX_NUMBERS) {
        pthread_cond_broadcast(&cond);
    }
    pthread_mutex_unlock(&mutex);

    pthread_barrier_wait(&barrier);

    int digit = abs(number % 10);

    pthread_mutex_lock(&mutex);

    if (firstThread) {
        printf("Thread %lu is the first to insert a value into the vectors.\n", pthread_self());
        firstThread = 0;
    }

    if (digit % 2 == 0) {
        U[U_size++] = number;
    } else {
        L[L_size++] = number;
    }

    S += number;

    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    int N;
    int numbers[MAX_NUMBERS];
    pthread_t threads[MAX_NUMBERS];
    ThreadParam threadParams[MAX_NUMBERS];

    pthread_mutex_init(&mutex, NULL);
    pthread_barrier_init(&barrier, NULL, MAX_NUMBERS + 1);
    pthread_cond_init(&cond, NULL);

    printf("Enter the number of elements (N): ");
    scanf("%d", &N);

    if (N <= 0 || N > MAX_NUMBERS) {
        printf("Invalid number of elements.\n");
        return 0;
    }

    printf("Enter %d numbers:\n", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &numbers[i]);
    }

    for (int i = 0; i < N; i++) {
        threadParams[i].number = numbers[i];
        pthread_create(&threads[i], NULL, processNumber, (void*)&threadParams[i]);
    }

    pthread_mutex_lock(&mutex);
    while (threads_ready < N) {
        pthread_cond_wait(&cond, &mutex);
    }
    pthread_mutex_unlock(&mutex);

    pthread_barrier_wait(&barrier);

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Vector L size: %d\n", L_size);
    printf("Vector U size: %d\n", U_size);
    printf("Value of S: %d\n", S);

    pthread_mutex_destroy(&mutex);
    pthread_barrier_destroy(&barrier);
    pthread_cond_destroy(&cond);

    return 0;
}

