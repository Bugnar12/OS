#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_NUMBERS 100

// Structure to pass multiple arguments to the thread function
struct ThreadArgs {
    int number;
    int S;
    int *L;
    int *U;
};

// Thread function
void *processNumber(void *arg) {
    struct ThreadArgs *args = (struct ThreadArgs *)arg;
    int number = args->number;
    int S = args->S;
    int *L = args->L;
    int *U = args->U;

    // Process the number in the thread
    // Replace this with your desired logic
    printf("Thread processed number: %d\n", number);
    printf("Thread S: %d\n", S);
    printf("Thread L[0]: %d\n", L[0]);
    printf("Thread U[0]: %d\n", U[0]);

    pthread_exit(NULL);
}

int main() {
    int N; // Number of threads
    int L[MAX_NUMBERS]; // Vector L
    int U[MAX_NUMBERS]; // Vector U
    int S; // Integer S
    pthread_t threads[MAX_NUMBERS]; // Thread IDs
    struct ThreadArgs threadArgs[MAX_NUMBERS]; // Arguments for each thread

    printf("Enter the number of threads (N): ");
    scanf("%d", &N);

    printf("Enter the elements of vector L: ");
    for (int i = 0; i < N; i++) {
        scanf("%d", &L[i]);
    }

    printf("Enter the elements of vector U: ");
    for (int i = 0; i < N; i++) {
        scanf("%d", &U[i]);
    }

    printf("Enter the value of integer S: ");
    scanf("%d", &S);

    // Create threads and pass arguments
    for (int i = 0; i < N; i++) {
        printf("Enter number for thread %d: ", i + 1);
        scanf("%d", &threadArgs[i].number);
        threadArgs[i].S = S;
        threadArgs[i].L = L;
        threadArgs[i].U = U;
        pthread_create(&threads[i], NULL, processNumber, (void *)&threadArgs[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
