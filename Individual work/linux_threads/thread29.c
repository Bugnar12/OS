#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_DIGITS 20
#define NUM_THREADS 5

char number[MAX_DIGITS + 1];
pthread_mutex_t mutex;

void* reverse_number(void* arg) {
    int thread_id = *(int*)arg;
    char temp;

    pthread_mutex_lock(&mutex);

    // Reverse the digits in the number
    int start = thread_id * (strlen(number) / NUM_THREADS);
    int end = start + (strlen(number) / NUM_THREADS) - 1;

    while (start < end) {
        temp = number[start];
        number[start] = number[end];
        number[end] = temp;
        end--;
    }

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    printf("Enter a number (at least 6 digits): ");
    fgets(number, sizeof(number), stdin);
    number[strcspn(number, "\n")] = '\0';

    if (strlen(number) < 6) {
        printf("Number must contain at least 6 digits.\n");
        return 1;
    }

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, reverse_number, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Reversed number: %s\n", number);

    pthread_mutex_destroy(&mutex);

    return 0;
}

