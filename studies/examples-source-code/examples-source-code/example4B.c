#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 5

void *aThread(void *arg)
{
 long tid=(long)arg;
 long square = tid*tid;     // A
 //double square = tid*tid; // B

 printf("thread %ld: Hello World !\n", tid);
 pthread_exit((void*)square);
}

int main()
{
 pthread_t threads[NUM_THREADS];
 long t; void *status;

 for(t=0;t<NUM_THREADS;t++){
     printf("thread main: creating thread %ld\n", t);
     pthread_create(&threads[t], NULL, aThread, (void *)t);
 }

 /* Wait for the other threads */
 for(t=0; t<NUM_THREADS; t++) {
     pthread_join(threads[t], &status);
     printf("thread main: joined with thread %ld: exit status is: %ld\n", t, (long)status); // A
     //printf("thread main: joined with thread %ld: exit status is: %f\n", t, (double)status); // B
 }

 printf("thread main: program completed: exiting\n");
 pthread_exit(NULL); 
}
