// create-many-threads.c

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 20000

void *aThread(void *tid)
{
  //pthread_detach(pthread_self()); // (*1)
  pthread_exit(NULL);
}

int main()
{
 pthread_t threads[NUM_THREADS];
 int ret;

 for(long t=0;t<NUM_THREADS;t++){
   ret = pthread_create(&threads[t], NULL, aThread, (void *)t);
   if (ret!=0){
     printf("Failed on the creation of thread t=%ld\n", t);
     printf("Return code from pthread_create() is %d\n", ret);
     exit(ret);
   }
   // pthread_detach(threads[t]); // (*2)
 }

 pthread_exit(NULL);
}
