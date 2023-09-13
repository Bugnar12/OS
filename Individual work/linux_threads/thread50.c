#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;
long long inputNumber;
long long reversedNumber = 0;
int numDigits = 0;
int threadsCompleted = 0;

void* reverseNumber(void* param) {
    long long threadNumber = *((long long*)param);

    long long threadReversedNumber = 0;
    long long remainder;

    while (inputNumber > 0) {
        remainder = inputNumber % 10;
        threadReversedNumber = (threadReversedNumber * 10) + remainder;
        inputNumber /= 10;
    }

    pthread_mutex_lock(&mutex);
    reversedNumber = (reversedNumber * 10) + threadReversedNumber;
    threadsCompleted++;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    printf("Enter a number with at least 6 digits: ");
    scanf("%lld", &inputNumber);

    if (inputNumber < 100000) {
        printf("You need to enter a number with at least 6 digits.\n");
        return 0;
    }

    pthread_t threads[5];
    pthread_mutex_init(&mutex, NULL);

    long long threadNumbers[5];
    for (int i = 0; i < 5; i++) {
        threadNumbers[i] = i + 1;
        pthread_create(&threads[i], NULL, reverseNumber, (void*)&threadNumbers[i]);
    }

    while (threadsCompleted < 5) {
        // Wait for threads to complete
    }

    pthread_mutex_destroy(&mutex);

    printf("Reversed number: %lld\n", reversedNumber);

    return 0;
}

