#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
#define M 13
#define SLEEP 4

sem_t lineSemaphore;
int lines[N];
pthread_t tid[M];
time_t start;

void* passThrough(void* arg) {
    int train = *(int*)arg;
    sleep(1 + rand() % SLEEP);  // Before => A
    printf("Train %d entered station A\n", train);
    
    // Wait until there is an available line
    sem_wait(&lineSemaphore);
    
    int line;
    for (line = 0; line < N; line++) {
        if (lines[line] == -1) {
            lines[line] = train;
            break;
        }
    }
    
    printf("Train %d passed from A to B on line %d\n", train, line);
    sleep(1 + rand() % SLEEP);  // A => B
    printf("Train %d arrived at station B and freed line %d\n", train, line);
    
    // Free the line
    lines[line] = -1;
    
    // Signal that a line is available
    sem_post(&lineSemaphore);
    
    return NULL;
}

int main() {
    int i;
    
    // Initialize semaphore
    sem_init(&lineSemaphore, 0, N);
    
    // Initialize lines
    for (i = 0; i < N; i++) {
        lines[i] = -1;
    }
    
    start = time(NULL);
    
    // Launch M threads, one for each train
    for (i = 0; i < M; i++) {
        pthread_create(&tid[i], NULL, passThrough, &i);
    }
    
    // Wait for all threads to finish
    for (i = 0; i < M; i++) {
        pthread_join(tid[i], NULL);
    }
    
    // Destroy semaphore
    sem_destroy(&lineSemaphore);
    
    return 0;
}

