#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10
int number=1;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

void* consumer(void *arg)
{
 while(1) {
     pthread_mutex_lock(&mutex);
     while (number % 2 != 0)
         pthread_cond_wait(&cond, &mutex);
     printf("consumer: number = %d\n", number);
     number=1;
     pthread_cond_broadcast(&cond); // (*)
     pthread_mutex_unlock(&mutex);
 }
 pthread_exit(NULL);
}

int main()
{
 pthread_t thread;  
 
 pthread_create(&thread, NULL, consumer, NULL);
 
 // producer
 int i=0; unsigned int seedp=getpid();
 while(++i <= N) {
     pthread_mutex_lock(&mutex);
     while(number % 2 == 0)
         pthread_cond_wait(&cond, &mutex);
     number = rand_r(&seedp) % 10;
     printf("producer: i = %d: number = %d\n", i, number);
     if (number % 2 == 0)
         pthread_cond_broadcast(&cond); // (*)
     pthread_mutex_unlock(&mutex);
 }
 pthread_cancel(thread);
 pthread_exit(NULL);
}
