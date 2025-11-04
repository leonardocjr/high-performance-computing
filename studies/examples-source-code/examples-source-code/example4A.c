#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 5

void *aThread(void *arg)
{
 long tid=(long)arg;

 printf("thread %ld: Hello World !\n", tid);
 pthread_exit(NULL);
}

int main()
{
 pthread_t threads[NUM_THREADS];
 pthread_attr_t attr;
 long t;

 /* Initialize and set thread detached attribute */
 pthread_attr_init(&attr);
 pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

 for(t=0;t<NUM_THREADS;t++){
     printf("thread main: creating thread %ld\n", t);
     pthread_create(&threads[t], &attr, aThread, (void *)t);
 }

 /* Free attribute and wait for the other threads */
 pthread_attr_destroy(&attr);

 /* Wait for the other threads */
 for(t=0; t<NUM_THREADS; t++) {
     pthread_join(threads[t], NULL);
     printf("thread main: joined with thread %ld\n", t);
 }

 printf("thread main: program completed: exiting\n");
 pthread_exit(NULL); 
}
