#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define MAX_WORDS 100
#define NUM_THREADS 5

// Global variables
char sentence[MAX_WORDS][100];
int sentence_length = 0;
pthread_mutex_t mutex;
int threads_completed = 0;

// Thread function
void* reverseWord(void* arg) {
    int index = *(int*)arg;

    // Extract the sentence pointer from the argument
    char (*sent)[100] = (char(*)[100])arg;

    pthread_mutex_lock(&mutex);
    if (index < sentence_length) {
        // Swap words in the sentence
        int rev_index = sentence_length - index - 1;
        char temp[100];
        strcpy(temp, sent[index]);
        strcpy(sent[index], sent[rev_index]);
        strcpy(sent[rev_index], temp);
    }
    threads_completed++;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    printf("Enter a sentence (at least 6 words): ");
    fgets(sentence[0], sizeof(sentence[0]), stdin);

    // Split the sentence into words
    char* token = strtok(sentence[0], " \n");
    while (token != NULL && sentence_length < MAX_WORDS) {
        strcpy(sentence[sentence_length++], token);
        token = strtok(NULL, " \n");
    }

    if (sentence_length < 6) {
        printf("Sentence must have at least 6 words.\n");
        return 1;
    }

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, reverseWord, sentence);
    }

    // Wait for threads to finish
    while (threads_completed < NUM_THREADS)
        ;

    // Display the result
    printf("Reversed sentence: ");
    for (int i = 0; i < sentence_length; i++) {
        printf("%s ", sentence[i]);
    }
    printf("\n");

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}

