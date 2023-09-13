#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define VECTOR_SIZE 1000
#define NUM_THREADS 5
#define EXTRACTION_THREADS 3
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

void *extract_closest(void *arg) {
    int thread_id = *(int *)arg;

    while (1) {
        pthread_mutex_lock(&mutex);

        if (count == 0) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        double mean = 0;
        for (int i = 0; i < count; i++) {
            mean += vector[i];
        }
        mean /= count;

        int closest_num = vector[0];
        double min_distance = fabs(mean - vector[0]);

        for (int i = 1; i < count; i++) {
            double distance = fabs(mean - vector[i]);
            if (distance < min_distance) {
                min_distance = distance;
                closest_num = vector[i];
            }
        }

        printf("Closest number to mean: %d\n", closest_num);

        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS + EXTRACTION_THREADS];
    int thread_ids[NUM_THREADS + EXTRACTION_THREADS];

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector[i] = 0;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, generate_numbers, &thread_ids[i]);
    }

    for (int i = NUM_THREADS; i < NUM_THREADS + EXTRACTION_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, extract_closest, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS + EXTRACTION_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
