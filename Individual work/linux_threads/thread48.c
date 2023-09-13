#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


#define THR_COUNT 5
pthread_mutex_t mutex;
char inputSentence[1000];
char** words;
int wordCount;
char* currentWord;
int flag1;
int flag2;

int counter;

char* reversedSentence;

void* reverseWord(void* param) {
    char* sentence = (char*)param;

    pthread_mutex_lock(&mutex);
    if (flag1 == 0) { 
        currentWord = strtok(sentence, " \n");
        words[0] = strdup(currentWord);
        flag1 = 1;
    }
    pthread_mutex_unlock(&mutex);

    while (currentWord != NULL) {
        pthread_mutex_lock(&mutex);
        wordCount++;
        currentWord = strtok(NULL, " \n");
        if (currentWord != NULL) {
            words[wordCount] = strdup(currentWord);
	}
        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_lock(&mutex);
    if (flag2 == 0) {
        counter = wordCount - 1;
        flag2 = 1;

        while (counter >= 0) {
            strcat(reversedSentence, words[counter]);
            strcat(reversedSentence, " ");
            counter--;
        }
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    printf("Enter the sentence: ");
    fgets(inputSentence, sizeof(inputSentence), stdin);

    pthread_threads_t[THR_COUNT];

    pthread_mutex_init(&mutex, NULL);

    // Allocate memory for words array
    words = (char**)malloc(100 * sizeof(char*));
    for (int i = 0; i < 100; i++) {
        words[i] = (char*)malloc(100 * sizeof(char));
    }

    // Allocate memory for reversedSentence
    reversedSentence = (char*)malloc(1000 * sizeof(char));

    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, reverseWord, inputSentence);
    }

    if (wordCount < 6) {
        printf("Input minimum 6 words : \n\n");

        // Free dynamically allocated memory
        for (int i = 0; i < 100; i++) {
            free(words[i]);
        }
        free(words);
        free(reversedSentence);

        return 1;
    }

    printf("%s\n", reversedSentence);

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    // Free dynamically allocated memory
    for (int i = 0; i < 100; i++) {
        free(words[i]);
    }
    free(words);
    free(reversedSentence);

    pthread_mutex_destroy(&mutex);
    return 0;
}

