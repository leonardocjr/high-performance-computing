#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // sleep
#include <errno.h> // ETIMEDOUT
#include <time.h> // struct timespec { time_t tv_sec; long tv_nsec;}

pthread_mutex_t GLOBAL_mutex = PTHREAD_MUTEX_INITIALIZER;
struct timespec GLOBAL_ts_future;

void *aThread (void *arg)
{
 long tid=(long)arg; int ret;
 
 ret=pthread_mutex_timedlock (&GLOBAL_mutex, &GLOBAL_ts_future);
 if (ret==0) {
    printf("thread %ld: before sleep\n",tid);
    sleep(5);
    printf("thread %ld: after sleep\n",tid);
    pthread_mutex_unlock (&GLOBAL_mutex);
 }
 else if (ret==ETIMEDOUT)
    printf("thread %ld: timeout happened\n",tid);

 printf("thread %ld: exiting\n",tid);
 pthread_exit(NULL);
}

int main()
{
 struct timespec ts_now; 
 pthread_t thread1,thread2;
 
 clock_gettime(CLOCK_REALTIME, &ts_now);
 GLOBAL_ts_future.tv_sec=ts_now.tv_sec+2; // A (timeout = 2s)
 //GLOBAL_ts_future.tv_sec=ts_now.tv_sec+6; // B (timeout = 6s)
 GLOBAL_ts_future.tv_nsec=0;
 
 pthread_create(&thread1, NULL, aThread, (void*)1);
 pthread_create(&thread2, NULL, aThread, (void*)2); 
 
 pthread_join(thread1, NULL);
 pthread_join(thread2, NULL);
 
 pthread_mutex_destroy(&GLOBAL_mutex);
 printf("thread main: ending\n");
 pthread_exit(NULL);
}
