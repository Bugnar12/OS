#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NUM_THREADS 5

pthread_mutex_t lock;
char** words;
int num_words;

void* reverse_word(void* arg) {
    int index = *(int*)arg;

    pthread_mutex_lock(&lock);
    char* temp = words[index];
    words[index] = words[num_words - 1 - index];
    words[num_words - 1 - index] = temp;
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

int main() {
    printf("Enter a sentence with at least 6 words: ");
    char sentence[1000];
    fgets(sentence, 1000, stdin);

    char* token = strtok(sentence, " ");
    num_words = 0;
    words = (char**)malloc(sizeof(char*) * 100);

    while (token != NULL) {
        words[num_words] = (char*)malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(words[num_words], token);
        num_words++;
        token = strtok(NULL, " ");
    }

    if (num_words < 6) {
        printf("Sentence should have at least 6 words.\n");
        return 1;
    }

    pthread_t threads[NUM_THREADS];
    int indices[NUM_THREADS];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        indices[i] = i;
        pthread_create(&threads[i], NULL, reverse_word, &indices[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Reversed sentence: ");
    for (int i = 0; i < num_words; i++) {
        printf("%s ", words[i]);
    }
    printf("\n");

    pthread_mutex_destroy(&lock);
    for (int i = 0; i < num_words; i++) {
        free(words[i]);
    }
    free(words);

    return 0;
}

