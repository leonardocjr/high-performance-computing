#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int flag_worker=0;
pthread_mutex_t mutex_worker=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_worker=PTHREAD_COND_INITIALIZER;
int flag_main=0;
pthread_mutex_t mutex_main=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_main=PTHREAD_COND_INITIALIZER;

void* worker(void *arg)
{ 
 printf("task A\n");
 pthread_mutex_lock(&mutex_worker);
 flag_worker=1;
 pthread_cond_signal(&cond_worker);
 pthread_mutex_unlock(&mutex_worker);
 
 pthread_mutex_lock(&mutex_main);
 while (flag_main != 1)
     pthread_cond_wait(&cond_main, &mutex_main);
 pthread_mutex_unlock(&mutex_main);
 printf("task C\n"); 
 
 pthread_exit(NULL);
}

int main()
{
 pthread_t thread;
 pthread_create(&thread, NULL, worker, NULL);

 pthread_mutex_lock(&mutex_worker);
 while (flag_worker != 1)
     pthread_cond_wait(&cond_worker, &mutex_worker);
 pthread_mutex_unlock(&mutex_worker);
 
 printf("task B\n");     
 pthread_mutex_lock(&mutex_main);
 flag_main=1;
 pthread_cond_signal(&cond_main);
 pthread_mutex_unlock(&mutex_main);
 
 pthread_exit(NULL);
}
