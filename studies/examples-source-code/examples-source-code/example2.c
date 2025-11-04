#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 5
typedef struct { long tid; char character; } longchar_t;

void *aThread(void *arg)
{
   longchar_t *args=(longchar_t*)arg;
   printf("thread %ld: character %c: Hello World !\n", args->tid, args->character);
   pthread_exit(NULL);
}

int main()
{
   pthread_t threads[NUM_THREADS]; longchar_t *params;
   long t;

   params=(longchar_t *)malloc(NUM_THREADS*sizeof(longchar_t));
   for(t=0;t<NUM_THREADS;t++){
     params[t].tid=t; params[t].character='a'+(int)t;
     printf("thread main: creating thread %ld\n", t);
     pthread_create(&threads[t], NULL, aThread, (void *)&params[t]);
   }

   printf("thread main: program completed: exiting\n");
   pthread_exit(NULL);    /* Last thing that main() should do */
}
