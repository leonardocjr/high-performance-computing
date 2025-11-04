#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h> // EBUSY

//note: make sure you use -O0 to compile; otherwise the code may run
//      so fast that GLOBAL_counter is not accessed simultaneously

#define NUM_THREADS 4
#define NUM_INCREMENTS 10000000
int GLOBAL_counter=0;

pthread_mutex_t GLOBAL_counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *aThread (void *arg)
{
 unsigned long failed_lock_attempts=0;
 
 for (int i=0; i<NUM_INCREMENTS; i++) {
   while (pthread_mutex_trylock (&GLOBAL_counter_mutex) == EBUSY)
       failed_lock_attempts ++;
   GLOBAL_counter ++;	 
   pthread_mutex_unlock (&GLOBAL_counter_mutex);
 }
 		
 pthread_exit((void*)failed_lock_attempts);
}

int main()
{
 long t; void *status;
 pthread_t threads[NUM_THREADS];

 /* Create worker threads to perform the increments */
 for(t=0;t<NUM_THREADS;t++)
   pthread_create(&threads[t], NULL, aThread, NULL); 
 
 /* Wait for the worker threads to end */
 for(t=0;t<NUM_THREADS;t++) {
   pthread_join(threads[t], &status);
   printf("thread %ld: failed_lock_attempts = %lu\n", t, (unsigned long)status);
 }

 /* Show value of the counter */
 printf("GLOBAL_counter is %d: should be %d\n", GLOBAL_counter, NUM_THREADS*NUM_INCREMENTS);
 
 pthread_mutex_destroy(&GLOBAL_counter_mutex);
 pthread_exit(NULL);
}
