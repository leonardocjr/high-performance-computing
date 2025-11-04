#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 4

pthread_barrier_t GLOBAL_barrier;

void *aThread(void *arg)
{
 long tid=(long)arg;

 printf("thread %ld: Hello World !\n", tid);
 
 // barrier
 pthread_barrier_wait(&GLOBAL_barrier);
 
 pthread_exit(NULL); 
}

int main()
{
 pthread_t threads[NUM_THREADS];
 long t;

 /* Initialize the barrier */   
 pthread_barrier_init(&GLOBAL_barrier, NULL, NUM_THREADS+1);
 
 /* Create the worker threads */
 for(t=0;t<NUM_THREADS;t++){
     //printf("thread main: creating thread %ld\n", t);
     pthread_create(&threads[t], NULL, aThread, (void *)t);
 }
 
 // barrier
 pthread_barrier_wait(&GLOBAL_barrier);
 
 printf("thread main: all worker threads completed: exiting\n"); 
 pthread_barrier_destroy(&GLOBAL_barrier);
 pthread_exit(NULL); 
}
