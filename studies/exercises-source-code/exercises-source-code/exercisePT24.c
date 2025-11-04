#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define PERIOD 100000000

char stop=0;
unsigned long long number=1;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

void* output(void *arg)
{
 while (1) {
     pthread_mutex_lock(&mutex);
     while(stop == 0)
         pthread_cond_wait(&cond, &mutex);
     printf("output: number %llu\n", number);
     stop=0;
     pthread_cond_signal(&cond);
     pthread_mutex_unlock(&mutex);
 }
 
 pthread_exit(NULL);
}

int main()
{
 pthread_t thread;
 
 pthread_create(&thread, NULL, output, NULL);
 
 while(1) {     
     pthread_mutex_lock(&mutex);
     while (stop == 1) 
         pthread_cond_wait(&cond, &mutex);
     number ++;
     if (number % PERIOD == 0) {
         stop=1;
         printf("count: number %llu\n", number);
         pthread_cond_signal(&cond);
     }
     pthread_mutex_unlock(&mutex);
 }
 pthread_exit(NULL);
}
