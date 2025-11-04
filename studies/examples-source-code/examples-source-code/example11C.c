#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h> // sleep

int GLOBAL_number=-1;
pthread_mutex_t GLOBAL_mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t GLOBAL_cond=PTHREAD_COND_INITIALIZER;

void* consumer(void *arg)
{
 int end_loop=0;
 do { 
     pthread_mutex_lock(&GLOBAL_mutex);
     // verify if the number was produced; if not, wait
     while (GLOBAL_number==-1) {
        printf("consumer: waiting\n");
        pthread_cond_wait(&GLOBAL_cond, &GLOBAL_mutex);
     }
     printf("consumer: %d\n", GLOBAL_number);
     if (GLOBAL_number==0) end_loop=1;
     else GLOBAL_number=-1;
     pthread_mutex_unlock(&GLOBAL_mutex); 
  } while (!end_loop); 
 
 pthread_exit(NULL);
}

int main() // producer
{
 pthread_t thread; int end_loop=0;
 
 pthread_create(&thread, NULL, consumer, NULL);

 do {
    //sleep(1); // make consumer gain lock first
    
    pthread_mutex_lock(&GLOBAL_mutex);
    printf("producer: "); scanf("%d", &GLOBAL_number);
    if (GLOBAL_number==0) end_loop=1;
    // notify consumer that the number was produced
    pthread_cond_signal(&GLOBAL_cond);
    pthread_mutex_unlock(&GLOBAL_mutex);
 } while (!end_loop); 
 
 pthread_join(thread, NULL);
 pthread_exit(NULL);
}
