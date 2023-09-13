#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_NUMBERS 100

int S = 0;
int L[MAX_NUMBERS];
int U[MAX_NUMBERS];
int L_count = 0;
int U_count = 0;
int num_threads = 0;
pthread_mutex_t mutex;
pthread_barrier_t barrier;

void* processNumber(void* arg) {
    int number = (int)arg;

    // Wait for all threads to be created
    pthread_barrier_wait(&barrier);

    // Check if the number starts with an even or odd digit
    if (number % 2 == 0) {
        pthread_mutex_lock(&mutex);
        if (U_count == 0) {
            printf("Thread %lu is the first to insert a value in vector U.\n", pthread_self());
        }
        U[U_count++] = number;
        pthread_mutex_unlock(&mutex);
    } else {
        pthread_mutex_lock(&mutex);
        if (L_count == 0) {
            printf("Thread %lu is the first to insert a value in vector L.\n", pthread_self());
        }
        L[L_count++] = number;
        pthread_mutex_unlock(&mutex);
    }

    // Add the number to the variable S
    pthread_mutex_lock(&mutex);
    S += number;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    int N;
    printf("Enter the number of elements (N): ");
    scanf("%d", &N);

    if (N <= 0 || N > MAX_NUMBERS) {
        printf("Invalid number of elements. Please try again.\n");
        return 0;
    }

    pthread_t threads[N];
    int numbers[N];

    // Initialize mutex and barrier
    pthread_mutex_init(&mutex, NULL);
    pthread_barrier_init(&barrier, NULL, N);

    printf("Enter %d numbers:\n", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &numbers[i]);
    }

    // Create threads
    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, processNumber, (void*)&numbers[i]);
        num_threads++;
    }

    // Wait for all threads to finish
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print the size of L, U, and the value of S
    printf("Size of vector L: %d\n", L_count);
    printf("Size of vector U: %d\n", U_count);
    printf("Value of S: %d\n", S);

    // Clean up mutex and barrier
    pthread_mutex_destroy(&mutex);
    pthread_barrier_destroy(&barrier);

    return 0;
}
