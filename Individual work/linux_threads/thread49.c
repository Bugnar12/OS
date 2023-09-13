#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t mutex;
char inputSentence[1000];
char** wordArray;
int wordCount;
char* currentWord;
int isProcessed1;
int indexCounter;
int isProcessed2;
char* reversedSentence;

void* reverseWordThread(void* param) {
    char* sentence = (char*)param;

    pthread_mutex_lock(&mutex);
    if (isProcessed1 == 0) {
        currentWord = strtok(sentence, " \n");
        wordArray[0] = strdup(currentWord);
        isProcessed1 = 1;
    }
    pthread_mutex_unlock(&mutex);

    while (currentWord != NULL) {
        pthread_mutex_lock(&mutex);
        wordCount++;
        currentWord = strtok(NULL, " \n");
        if (currentWord != NULL) {
            wordArray[wordCount] = strdup(currentWord);
        }
        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_lock(&mutex);
    if (isProcessed2 == 0) {
        indexCounter = wordCount - 1;
        isProcessed2 = 1;

        while (indexCounter >= 0) {
            strcat(reversedSentence, wordArray[indexCounter]);
            strcat(reversedSentence, " ");
            indexCounter--;
        }
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    printf("Enter the sentence: ");
    fgets(inputSentence, sizeof(inputSentence), stdin);

    pthread_t threads[5];

    pthread_mutex_init(&mutex, NULL);

    // Allocate memory for wordArray
    wordArray = (char**)malloc(100 * sizeof(char*));
    for (int i = 0; i < 100; i++) {
        wordArray[i] = (char*)malloc(100 * sizeof(char));
    }

    // Allocate memory for reversedSentence
    reversedSentence = (char*)malloc(1000 * sizeof(char));

    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, reverseWordThread, inputSentence);
    }

    if (wordCount < 6) {
        printf("You need to enter at least 6 words\n");

        // Free dynamically allocated memory
        for (int i = 0; i < 100; i++) {
            free(wordArray[i]);
        }
        free(wordArray);
        free(reversedSentence);

        return 0;
    }

    printf("%s\n", reversedSentence);

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    // Free dynamically allocated memory
    for (int i = 0; i < 100; i++) {
        free(wordArray[i]);
    }
    free(wordArray);
    free(reversedSentence);

    pthread_mutex_destroy(&mutex);
    return 0;
}

