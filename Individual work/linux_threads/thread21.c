#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define VECTOR_SIZE 1000000
#define NUM_THREADS 5
#define DISPLAY_INTERVAL 10

int vector[VECTOR_SIZE];
int count = 0;

pthread_mutex_t mutex;

void display_vector() {
    printf("Current vector: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");
}

void *generate_numbers(void *arg) {
    int thread_id = *(int *)arg;
    int start = thread_id * (VECTOR_SIZE / NUM_THREADS);
    int end = start + (VECTOR_SIZE / NUM_THREADS);

    for (int i = start; i < end; i++) {
        int num = rand() % 1000;

        pthread_mutex_lock(&mutex);

        int j = count - 1;
        while (j >= 0 && num < vector[j]) {
            vector[j + 1] = vector[j];
            j--;
        }

        vector[j + 1] = num;
        count++;

        if (count % DISPLAY_INTERVAL == 0) {
            display_vector();
        }

        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL);

    clock_t start_time = clock(); // Start measuring runtime

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, generate_numbers, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t end_time = clock(); // Stop measuring runtime
    double runtime = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    display_vector();
    printf("Runtime: %.3f seconds\n", runtime);

    pthread_mutex_destroy(&mutex);

    return 0;
}

