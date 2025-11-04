#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define NUM_THREADS 5

char *messages[NUM_THREADS]={"English: Hello World!","French: Bonjour, le monde!","Spanish: Hola al mundo",
                             "German: Guten Tag, Welt!","Russian: Zdravstvytye, mir!"};
                             
void *aThread(void *arg)
{
   long tid=(long)arg;

   printf("Process %d: thread %ld: %s\n", getpid(), tid, messages[tid]);
   pthread_exit(NULL);
}

int main()
{
   pthread_t threads[NUM_THREADS];
   long t;

   for(t=0;t<NUM_THREADS;t++){
     printf("Process %d: thread main: creating thread %ld\n", getpid(), t);
     pthread_create(&threads[t], NULL, aThread, (void *)t);
   }
   
   printf("Process %d: thread main: program completed: exiting\n",getpid());
   pthread_exit(NULL);
}
