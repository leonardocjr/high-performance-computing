#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h> // avoid -Wpointer-to-int-cast

pthread_t thread_main;

void *aThread(void *arg)
{
   long tid=(long)arg; int ret; void *status;
   
   for (int i=0; i<5*tid; i++) { printf("thread %ld: i=%d\n", tid, i); sleep(1); }
   
   printf("thread %ld: going to join with thread main\n", tid);
   ret = pthread_join(thread_main, &status);
   
   if (ret==0) printf("thread %ld: SUCCESS; thread main returned %d\n", tid, (int)(uintptr_t)status); 
   else if (ret==EINVAL) printf("thread %ld: ERROR; thread main is not a joinable thread or another thread is already waiting to join with main\n", tid); 
   else if (ret==ESRCH) printf("thread %ld: ERROR; thread main does not exist\n", tid); 
   else printf("thread %ld: ERROR; thread main could not be joined due to reason %d\n", tid, ret); 
   
   printf("thread %ld: going to die\n", tid);
   pthread_exit(NULL);
}

int main()
{
   pthread_t thread1, thread2;
   
   thread_main=pthread_self();
   
   //pthread_detach(thread_main); // (*)
   
   pthread_create(&thread1, NULL, aThread, (void *)1);   
   pthread_create(&thread2, NULL, aThread, (void *)2);
   
   printf("thread main: going to die\n");
   pthread_exit((void*)3);
}
