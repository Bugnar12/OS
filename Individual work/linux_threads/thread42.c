#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NUM_THREADS 5

pthread_mutex_t lock;
char* sentence;

void* reverse_words(void* arg) {
    int index = *(int*)arg;
    char* start = sentence;

    int word_count = 0;
    while (*start && word_count < index) {
        if (*start == ' ') {
            word_count++;
        }
        start++;
    }

    char* end = start;
    while (*end && *end != ' ') {
        end++;
    }
    end--;

    while (start < end) {
        char temp = *start;
        *start++ = *end;
        *end-- = temp;
    }

    pthread_exit(NULL);
}

int main() {
    printf("Enter a sentence with at least 6 words: ");
    char input_sentence[1000];
    fgets(input_sentence, 1000, stdin);

    sentence = (char*)malloc(sizeof(char) * (strlen(input_sentence) + 1));
    strcpy(sentence, input_sentence);

    pthread_t threads[NUM_THREADS];
    int indices[NUM_THREADS];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        indices[i] = i;
        pthread_create(&threads[i], NULL, reverse_words, &indices[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Reversed sentence: %s\n", sentence);

    pthread_mutex_destroy(&lock);
    free(sentence);

    return 0;
}
