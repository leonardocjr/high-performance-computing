#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 5
typedef struct { float num; char character; } floatchar_t;
floatchar_t params[NUM_THREADS];

void *aThread(void *arg)
{
   long tid=(long)arg;

   printf("thread %ld: num %f: character %c: Hello World !\n", tid, params[tid].num, params[tid].character);
   pthread_exit(NULL);
}

int main()
{
   pthread_t threads[NUM_THREADS]; 
   long t;

   for(t=0;t<NUM_THREADS;t++){
     params[t].num=(float)t; params[t].character='a'+(int)t;
     printf("thread main: creating thread %ld\n", t);
     pthread_create(&threads[t], NULL, aThread, (void *)t);
   }
   
   printf("thread main: program completed: exiting\n");
   pthread_exit(NULL);    /* Last thing that main() should do */
}
