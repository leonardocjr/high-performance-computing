#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 4

int GLOBAL_counter = NUM_THREADS;
pthread_mutex_t GLOBAL_counter_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t GLOBAL_counter_cond = PTHREAD_COND_INITIALIZER;

void *aThread(void *arg)
{
 long tid=(long)arg;

 printf("thread %ld: Hello World !\n", tid);
 
 pthread_mutex_lock (&GLOBAL_counter_mutex);
 GLOBAL_counter --;	 
 if (GLOBAL_counter == 0)
    pthread_cond_signal(&GLOBAL_counter_cond);
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
 pthread_mutex_lock (&GLOBAL_counter_mutex); 
 while (GLOBAL_counter != 0)
    pthread_cond_wait(&GLOBAL_counter_cond, &GLOBAL_counter_mutex);
 pthread_mutex_unlock (&GLOBAL_counter_mutex);
 
 printf("thread main: all worker threads completed: exiting\n"); 
 pthread_mutex_destroy(&GLOBAL_counter_mutex);
 pthread_cond_destroy(&GLOBAL_counter_cond);
 pthread_exit(NULL); 
}
