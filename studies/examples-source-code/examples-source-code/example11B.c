#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h> // sleep
#include <errno.h> // ETIMEDOUT
#include <time.h> // struct timespec { time_t tv_sec; long tv_nsec;}

int GLOBAL_number=-1;
pthread_mutex_t GLOBAL_mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t GLOBAL_cond=PTHREAD_COND_INITIALIZER;

void* consumer(void *arg)
{
 int ret=-1; struct timespec ts_now, ts_future;
 clock_gettime(CLOCK_REALTIME, &ts_now);
 ts_future.tv_sec=ts_now.tv_sec+5; //(timeout=5s)
 ts_future.tv_nsec=0;
 
 pthread_mutex_lock(&GLOBAL_mutex);
 // verify if the number was produced; if not, wait up to 5s
 while (GLOBAL_number==-1 && ret != ETIMEDOUT) {
     printf("consumer: waiting\n");
     ret=pthread_cond_timedwait(&GLOBAL_cond, &GLOBAL_mutex, &ts_future);
 }
 if (ret == ETIMEDOUT) printf("consumer: timedout\n");
 else printf("consumer: %d\n", GLOBAL_number);
 pthread_mutex_unlock(&GLOBAL_mutex);

 pthread_exit(NULL);
}

int main() // producer
{
 pthread_t thread; 
 
 pthread_create(&thread, NULL, consumer, NULL);
 //sleep(1); // make consumer gain the lock first
 
 pthread_mutex_lock(&GLOBAL_mutex);
 printf("producer: "); scanf("%d", &GLOBAL_number);
 // notify consumer that the number was produced
 pthread_cond_signal(&GLOBAL_cond);
 pthread_mutex_unlock(&GLOBAL_mutex);

 pthread_join(thread, NULL);
 pthread_exit(NULL);
}
