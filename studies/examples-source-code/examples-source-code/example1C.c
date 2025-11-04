#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define NUM_THREADS 5

void *aThread(void *arg)
{
   long tid=*(long*)arg;

   printf("Process %d: thread %ld: Hello World !\n", getpid(), tid);
   pthread_exit(NULL);
}

int main()
{
   pthread_t threads[NUM_THREADS]; long *tids;
   long t;

   tids=(long*)malloc(NUM_THREADS*sizeof(long));
   for(t=0;t<NUM_THREADS;t++){
     tids[t]=t;
     printf("Process %d: thread main: creating thread %ld\n", getpid(), t);
     pthread_create(&threads[t], NULL, aThread, (void *)&tids[t]);
   }
   
   printf("Process %d: thread main: program completed: exiting\n",getpid());
   pthread_exit(NULL);
}
