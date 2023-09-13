#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_WORDS 50
#define NUM_THREADS 5

char sentence[MAX_WORDS][50];
int word_count = 0;
pthread_mutex_t mutex;

void* reverse_word(void* arg) {
    int thread_id = *(int*)arg;
    char temp[50];

    pthread_mutex_lock(&mutex);

    // Reverse the word in the corresponding position
    int start = thread_id * (word_count / NUM_THREADS);
    int end = start + (word_count / NUM_THREADS);

    for (int i = start; i < end; i++) {
        int len = strlen(sentence[i]);
        for (int j = 0; j < len / 2; j++) {
            temp[j] = sentence[i][len - 1 - j];
            temp[len - 1 - j] = sentence[i][j];
        }
        temp[len] = '\0';
        strcpy(sentence[i], temp);
    }

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    printf("Enter a sentence (at least 6 words): ");
    fgets(sentence[word_count], 50, stdin);

    // Tokenize the sentence into words
    char* word = strtok(sentence[word_count], " \n");
    while (word != NULL) {
        word_count++;
        strcpy(sentence[word_count], word);
        word = strtok(NULL, " \n");
    }

    if (word_count < 6) {
        printf("Sentence must contain at least 6 words.\n");
        return 1;
    }

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, reverse_word, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Reversed sentence: ");
    for (int i = 0; i < word_count; i++) {
        printf("%s ", sentence[i]);
    }
    printf("\n");

    pthread_mutex_destroy(&mutex);

    return 0;
}

