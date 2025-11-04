#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // sleep
#include <errno.h> // EBUSY = 16

pthread_mutex_t GLOBAL_counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *aThread (void *arg)
{
 long tid=(long)arg;
 
 pthread_mutex_lock (&GLOBAL_counter_mutex); // NOT a cancellation point
 printf("%ld: before sleep\n",tid);
 sleep(5); // a cancellation point
 printf("%ld: after sleep\n",tid);
 pthread_mutex_unlock (&GLOBAL_counter_mutex);

 pthread_exit(NULL);
}

int main()
{
 int ret;
 pthread_t thread1,thread2;
 
 pthread_mutex_lock (&GLOBAL_counter_mutex);
 
 pthread_create(&thread1, NULL, aThread, (void*)1);
 pthread_create(&thread2, NULL, aThread, (void*)2);
 
 pthread_mutex_unlock (&GLOBAL_counter_mutex);
 
 sleep(2); //A ("ensure" threads 1 and 2 reach pthread_mutex_lock)
 pthread_cancel(thread1); //B
 pthread_cancel(thread2); //C
 
 //pthread_join(thread1, NULL); //D
 //pthread_join(thread2, NULL); //E
 
 sleep(2); //F ("ensure" thread 1 and 2 reach pthread_mutex_lock)
 ret=pthread_mutex_destroy(&GLOBAL_counter_mutex); //G
 printf("main: ret=%d\n", ret); //G
 pthread_exit(NULL);
}
