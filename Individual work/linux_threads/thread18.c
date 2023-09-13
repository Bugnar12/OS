#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>

#define MAX_PARAMS 10

// Structure to pass multiple arguments to the thread function
struct ThreadArgs {
    char *param;
    int vowelCount;
    int consonantCount;
};

// Thread function
void *countCharacters(void *arg) {
    struct ThreadArgs *args = (struct ThreadArgs *)arg;
    char *param = args->param;
    int vowelCount = 0;
    int consonantCount = 0;

    // Count the vowels and consonants in the parameter
    for (int i = 0; i < strlen(param); i++) {
        char ch = param[i];
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            ch = tolower(ch);
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
                vowelCount++;
            else
                consonantCount++;
        }
    }

    // Update the counts in the thread arguments
    args->vowelCount = vowelCount;
    args->consonantCount = consonantCount;

    pthread_exit(NULL);
}

int main(int argc, char **argv) {
    int numParams = argc - 1; // Number of parameters
    pthread_t threads[MAX_PARAMS]; // Thread IDs
    struct ThreadArgs threadArgs[MAX_PARAMS]; // Arguments for each thread

    if (numParams > MAX_PARAMS) {
        printf("Error: Maximum number of parameters exceeded.\n");
        return 1;
    }

    // Create threads and pass arguments
    for (int i = 0; i < numParams; i++) {
        threadArgs[i].param = argv[i + 1];
        threadArgs[i].vowelCount = 0;
        threadArgs[i].consonantCount = 0;
        pthread_create(&threads[i], NULL, countCharacters, (void *)&threadArgs[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < numParams; i++) {
        pthread_join(threads[i], NULL);
        printf("Parameter: %s\n", threadArgs[i].param);
        printf("Vowel count: %d\n", threadArgs[i].vowelCount);
        printf("Consonant count: %d\n", threadArgs[i].consonantCount);
        printf("\n");
    }

    return 0;
}

