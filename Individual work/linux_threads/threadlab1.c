#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int is_prime(int num) {
    if (num <= 1)
        return 0;

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return 0;
    }

    return 1;
}

typedef struct {
    int start;
    int end;
    int count;
} PrimeThreadData;

void* count_primes(void* arg) {
    PrimeThreadData* threadData = (PrimeThreadData*)arg;

    int count = 0;
    for (int i = threadData->start; i <= threadData->end; i++) {
        if (is_prime(i))
            count++;
    }

    threadData->count = count;

    return NULL;
}

int main() {
    const int numThreads[] = {1, 2, 4, 8};
    const int intervalStart = 1;
    const int intervalEnd = 2000000;
    const int intervalSize = (intervalEnd - intervalStart + 1) / numThreads[3];

    time_t t1, t2;
    double executionTime;

    printf("Numarul de numere prime in intervalul %d-%d:\n", intervalStart, intervalEnd);

    for (int i = 0; i < sizeof(numThreads) / sizeof(numThreads[0]); i++) {
        int numPrimes = 0;
        pthread_t threads[numThreads[i]];
        PrimeThreadData threadData[numThreads[i]];

        t1 = time(NULL);

        for (int j = 0; j < numThreads[i]; j++) {
            threadData[j].start = intervalStart + j * intervalSize;
            threadData[j].end = threadData[j].start + intervalSize - 1;

            if (j == numThreads[i] - 1)
                threadData[j].end = intervalEnd;

            pthread_create(&threads[j], NULL, count_primes, &threadData[j]);
        }

        for (int j = 0; j < numThreads[i]; j++) {
            pthread_join(threads[j], NULL);
            numPrimes += threadData[j].count;
        }

        t2 = time(NULL);
        executionTime = difftime(t2, t1);

        printf("Numarul de numere prime cu %d thread-uri: %d\n", numThreads[i], numPrimes);
        printf("Timpul de executie cu %d thread-uri: %.0f secunde\n", numThreads[i], executionTime);
    }

    return 0;
}

