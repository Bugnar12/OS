#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t mutex;
char inputNumber[20];
char reversedNumber[20];
int threadsCompleted = 0;

void* reverseNumber(void* param) {
    char* threadNumber = (char*)param;
    int threadLength = strlen(threadNumber);

    for (int i = 0; i < threadLength / 2; i++) {
        char temp = threadNumber[i];
        threadNumber[i] = threadNumber[threadLength - i - 1];
        threadNumber[threadLength - i - 1] = temp;
    }

    pthread_mutex_lock(&mutex);
    strcat(reversedNumber, threadNumber);
    threadsCompleted++;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    printf("Enter a number with at least 6 digits: ");
    fgets(inputNumber, sizeof(inputNumber), stdin);
    inputNumber[strcspn(inputNumber, "\n")] = '\0';

    if (strlen(inputNumber) < 6) {
        printf("You need to enter a number with at least 6 digits.\n");
        return 0;
    }

    pthread_t threads[5];
    pthread_mutex_init(&mutex, NULL);

    int threadLength = strlen(inputNumber);
    int chunkSize = threadLength / 5;
    int remainingSize = threadLength % 5;
    int startIndex = 0;

    for (int i = 0; i < 5; i++) {
        int chunkEndIndex = startIndex + chunkSize;

        if (i < remainingSize) {
            chunkEndIndex++;
        }

        char threadNumber[20];
        strncpy(threadNumber, inputNumber + startIndex, chunkEndIndex - startIndex);
        threadNumber[chunkEndIndex - startIndex] = '\0';

        pthread_create(&threads[i], NULL, reverseNumber, (void*)threadNumber);

        startIndex = chunkEndIndex;
    }

    while (threadsCompleted < 5) {
        // Wait for threads to complete
    }

    pthread_mutex_destroy(&mutex);

    printf("Reversed number: %s\n", reversedNumber);

    return 0;
}

