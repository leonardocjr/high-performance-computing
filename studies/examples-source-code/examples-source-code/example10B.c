#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h> // EBUSY

//note: make sure you use -O0 to compile; otherwise the code may run
//      so fast that GLOBAL_counter is not accessed simultaneously

#define NUM_THREADS 4
#define NUM_INCREMENTS 10000000
int GLOBAL_counter=0;

pthread_rwlock_t GLOBAL_counter_rwlock = PTHREAD_RWLOCK_INITIALIZER;

void *aThread (void *arg)
{
 unsigned long failed_lock_attempts=0;
 int local_counter; 
 
 for (int i=0; i<NUM_INCREMENTS; i++) {
   //while (pthread_rwlock_trywrlock (&GLOBAL_counter_rwlock) == EBUSY) // A
   while (pthread_rwlock_tryrdlock (&GLOBAL_counter_rwlock) == EBUSY) // B
       failed_lock_attempts ++;   
   local_counter = GLOBAL_counter ++;
   pthread_rwlock_unlock (&GLOBAL_counter_rwlock);
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
 
 pthread_rwlock_destroy(&GLOBAL_counter_rwlock);
 pthread_exit(NULL);
}
