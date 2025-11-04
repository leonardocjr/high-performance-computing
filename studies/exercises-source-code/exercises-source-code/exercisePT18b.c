#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 4

int GLOBAL_counter = NUM_THREADS;
pthread_mutex_t GLOBAL_counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *aThread(void *arg)
{
 long tid=(long)arg;

 printf("thread %ld: Hello World !\n", tid);
 
 pthread_mutex_lock (&GLOBAL_counter_mutex);
 GLOBAL_counter --;	 
 pthread_mutex_unlock (&GLOBAL_counter_mutex);
 
 pthread_exit(NULL); 
}

int main()
{
 pthread_t threads[NUM_THREADS];
 long t;
    
 /* Create the worker threads */
 for(t=0;t<NUM_THREADS;t++){
     //printf("thread main: creating thread %ld\n", t);
     pthread_create(&threads[t], NULL, aThread, (void *)t);
 }

 /* Wait for the worker threads */
 while (GLOBAL_counter != 0);
 /*
 int counter_is_zero=0;
 while (!counter_is_zero) {
     pthread_mutex_lock (&GLOBAL_counter_mutex);
	 if (GLOBAL_counter == 0) counter_is_zero=1;
     pthread_mutex_unlock (&GLOBAL_counter_mutex);
 }
 */
 
 printf("thread main: all worker threads completed: exiting\n"); 
 pthread_mutex_destroy(&GLOBAL_counter_mutex);
 pthread_exit(NULL); 
}
