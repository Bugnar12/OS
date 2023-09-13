#include <stdio.h>
#include <pthread.h>

int n = 0;
pthread_mutex_t m[3];
pthread_cond_t cond[3];  // New condition variables

void* f(void* p) {
    int id = (int)p;
    pthread_mutex_lock(&m[id]);

    if (n < id) {  // Wait until the previous thread updates n
        pthread_cond_wait(&cond[id], &m[id]);
    }

    n += id;
    printf("%d ", n);
    fflush(stdout);  // Add fflush to ensure immediate output

    pthread_cond_broadcast(&cond[(id + 1) % 3]);  // Signal the next thread to proceed
    pthread_mutex_unlock(&m[id]);
    return NULL;
}

int main() {
    int i;
    pthread_t t[3];

    for (i = 0; i < 3; i++) {
        pthread_mutex_init(&m[i], NULL);
        pthread_cond_init(&cond[i], NULL);
    }

    for (i = 0; i < 3; i++) {
        pthread_create(&t[i], NULL, f, (void*)i);
    }

    for (i = 0; i < 3; i++) {
        pthread_join(t[i], NULL);
    }

    for (i = 0; i < 3; i++) {
        pthread_mutex_destroy(&m[i]);
        pthread_cond_destroy(&cond[i]);
    }

    return 0;
}

