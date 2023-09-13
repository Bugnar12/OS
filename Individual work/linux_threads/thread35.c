#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 5

pthread_mutex_t lock;
char* number;
int num_length;

void* reverse_digit(void* arg) {
    int index = *(int*)arg;

    pthread_mutex_lock(&lock);
    char temp = number[index];
    number[index] = number[num_length - 1 - index];
    number[num_length - 1 - index] = temp;
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

int main() {
    printf("Enter a number with at least 6 digits: ");
    number = (char*)malloc(sizeof(char) * 100);
    fgets(number, 100, stdin);

    num_length = strlen(number) - 1;  // Exclude the newline character

    if (num_length < 6) {
        printf("Number should have at least 6 digits.\n");
        return 1;
    }

    pthread_t threads[NUM_THREADS];
    int indices[NUM_THREADS];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        indices[i] = i;
        pthread_create(&threads[i], NULL, reverse_digit, &indices[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Reversed number: %s\n", number);

    pthread_mutex_destroy(&lock);
    free(number);

    return 0;
}

