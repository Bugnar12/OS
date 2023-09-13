#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_DIGITS 20
#define NUM_THREADS 7

char number[MAX_DIGITS + 1];
char reversed_number[MAX_DIGITS + 1];
pthread_mutex_t mutex;

void* reverse_digit(void* arg) {
    int digit_index = *(int*)arg;

    pthread_mutex_lock(&mutex);

    // Reverse the digit
    reversed_number[digit_index] = number[strlen(number) - 1 - digit_index];

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
        pthread_create(&threads[i], NULL, reverse_digit, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS - 1; i++) {  // Iterate up to NUM_THREADS - 1
        pthread_join(threads[i], NULL);
    }

    reversed_number[strlen(number)] = '\0';

    printf("Reversed number: %s\n", reversed_number);

    pthread_mutex_destroy(&mutex);

    return 0;
}

