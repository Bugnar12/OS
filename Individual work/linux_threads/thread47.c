#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
pthread_mutex_t m;
char sentence[1000];
char words[100][100];
int word_count;
char* word;
int ok;
int counter;
int ok2;
char reverse_sentence[1000];
void* reverse(void* param)
{

        char* sentence = (char*)param;

        pthread_mutex_lock(&m);
        if(ok == 0)
        {
                word = strtok(sentence, " \n");
                strcpy(words[0], word);
                ok = 1;
        }
        pthread_mutex_unlock(&m);

        while(word != NULL)
        {
                pthread_mutex_lock(&m);
                word_count++;
                word = strtok(NULL, " \n");
                if(word != NULL)
                {
                        strcpy(words[word_count], word);
                }
                pthread_mutex_unlock(&m);
        }

        pthread_mutex_lock(&m);


        if(ok2 == 0)
        {
                counter = word_count - 1;


                ok2 = 1;

                while(counter >= 0)
                {

                        strcat(reverse_sentence, words[counter]);
                        strcat(reverse_sentence, " ");
                        counter--;

                }
        }
        pthread_mutex_unlock(&m);
        pthread_exit(NULL);

}

int main(int argc, char** argv)
{
        printf("Enter the sencte: ");
        fgets(sentence, 1000, stdin);

        pthread_t t[5];

        pthread_mutex_init(&m, NULL);

        for(int i = 0; i < 5; i++)
        {
                pthread_create(&t[i], NULL, reverse, sentence);
        }

        if(word_count < 6)
        {
                printf("You need to enter at least 6 words\n");
                return 0;
        }
        printf("%s\n", reverse_sentence);

        for(int i = 0; i < 5; i++)
                pthread_join(t[i], NULL);
        pthread_mutex_destroy(&m);
        return 0;

}
