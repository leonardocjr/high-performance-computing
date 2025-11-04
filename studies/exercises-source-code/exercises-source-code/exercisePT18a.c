#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 4

char GLOBAL_flags[NUM_THREADS];

void *aThread(void *arg)
{
 long tid=(long)arg;

 printf("thread %ld: Hello World !\n", tid);
 GLOBAL_flags[tid]=0;
 
 pthread_exit(NULL);
}

int main()
{
 pthread_t threads[NUM_THREADS];
 long t;

 /* Reset the flags */
 for(t=0;t<NUM_THREADS;t++)
     GLOBAL_flags[t]=1;
    
 /* Create the worker threads */
 for(t=0;t<NUM_THREADS;t++){
     //printf("thread main: creating thread %ld\n", t);
     pthread_create(&threads[t], NULL, aThread, (void *)t);
 }

 /* Wait for the worker threads */
 for(t=0;t<NUM_THREADS;t++)
    while(GLOBAL_flags[t]);
 
 printf("thread main: all worker threads completed: exiting\n"); 
 pthread_exit(NULL); 
}
