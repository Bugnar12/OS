#include <stdlib.h>

#include <stdio.h>

#include <pthread.h>

#include <time.h>

#include <unistd.h>



int THR = 5;

int N = 100;

int nextn = 1;

pthread_mutex_t mtx_nextn = PTHREAD_MUTEX_INITIALIZER;



double sumf = 0;

pthread_mutex_t mtx_sumf = PTHREAD_MUTEX_INITIALIZER;



void *sumafactorial(void* p)

{

    printf("Thread %d started!\n", pthread_self());

    while (1)

    {

        int n = 0;

        pthread_mutex_lock(&mtx_nextn);

        n = nextn++;

        pthread_mutex_unlock(&mtx_nextn);



        if (n > N)

        {

            break;

        }



        double f = 1;

        printf("Thread %d calculeaza %d!\n", pthread_self(), n);

        for (int i = 1; i < n; i++)

        {

            f *= i;

        }




        pthread_mutex_lock(&mtx_sumf);

        sumf += f;

        pthread_mutex_unlock(&mtx_sumf);

    }



    return NULL;

}





int main()

{

    pthread_t tids[THR];



    for (int i = 0; i < THR; i++)

    {

        pthread_create(&tids[i], NULL, sumafactorial, NULL);

    }



    //int a;

    //scanf("%d", &a);



    for (int i = 0; i < THR; i++)

    {

        pthread_join(tids[i], NULL);

    }



    printf("Suma factorialelor pana la %d este %f\n", N, sumf);



    return;

}
