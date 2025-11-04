#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 5

pthread_barrier_t GLOBAL_barrier;

void *aThread(void *arg)
{
 long tid=(long)arg;
 
 for (int i=0; i<10; i++) {
    printf("thread %ld: i=%d\n", tid, i);
    pthread_barrier_wait(&GLOBAL_barrier);
 }
 
 pthread_exit(NULL);
}

int main()
{
 pthread_t threads[NUM_THREADS];
 long t; int ret;

 ret = pthread_barrier_init(&GLOBAL_barrier, NULL, NUM_THREADS);
 if (ret){
     printf("ERROR; return code from pthread_barrier_init() is %d\n", ret);
     exit(ret);
 }
 
 for(t=0;t<NUM_THREADS;t++){
     printf("thread main: creating thread %ld\n", t);
     ret = pthread_create(&threads[t], NULL, aThread, (void *)t);
     if (ret){
         printf("ERROR; return code from pthread_create() is %d\n", ret);
         exit(ret);
     }
 }

 for(t=0; t<NUM_THREADS; t++) {
     ret = pthread_join(threads[t], NULL);
     if (ret) {
         printf("ERROR; return code from pthread_join() is %d\n", ret);
         exit(ret);
     }
     printf("thread main: joined with thread %ld\n", t);
 }

 pthread_barrier_destroy(&GLOBAL_barrier); // safe only after joining
 printf("thread main: exiting\n"); 
 pthread_exit(NULL); 
}
