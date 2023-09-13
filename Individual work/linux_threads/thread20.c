#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define VECTOR_SIZE 1000
#define NUM_THREADS 5
#define DISPLAY_INTERVAL 10
i
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
    int thread_id = *(int *)arg; //the argument passed
    int start = thread_id * (VECTOR_SIZE / NUM_THREADS); //0-200, 200-400, 400-600, 600-800, 800-1000
    int end = start + (VECTOR_SIZE / NUM_THREADS);

    for (int i = start; i < end; i++) { ///each thread enters here
        int num = rand() % 1000;

        pthread_mutex_lock(&mutex); //each thread stops here:)

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

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, generate_numbers, (void*)&thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    display_vector();

    pthread_mutex_destroy(&mutex);

    return 0;
}

