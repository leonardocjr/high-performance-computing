#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

//https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_condattr_getclock.html
//https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_condattr_setclock.html
//https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_condattr_getpshared.html
//https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_condattr_setpshared.html

// time.h defines:
/*
enum clockid_e
{
  CLOCK_REALTIME           = 1,
#define CLOCK_REALTIME           CLOCK_REALTIME
};
typedef enum clockid_e clockid_t;
*/

void show_clock_id (int clock_id)
{
 printf("clock_id is %d\n", clock_id);
}

void show_pshared (int pshared)
{    	
 if (pshared == PTHREAD_PROCESS_PRIVATE)
   printf("pshared is PTHREAD_PROCESS_PRIVATE\n");
 else if (pshared == PTHREAD_PROCESS_SHARED)
   printf("pshared is PTHREAD_PROCESS_SHARED\n");
}

int main ()
{
 pthread_condattr_t attr;
 int ret, clock_id, pshared;

 ret = pthread_condattr_init(&attr);
 if (ret != 0) return ret;

 //ret = pthread_condattr_setclock(&attr, 1);
 //if (ret != 0) return ret;
 ret = pthread_condattr_getclock(&attr, &clock_id);
 if (ret != 0) return ret; else show_clock_id(clock_id);

 //ret = pthread_condattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
 //if (ret != 0) return ret;
 ret = pthread_condattr_getpshared(&attr, &pshared);
 if (ret != 0) return ret; else show_pshared(pshared);

 pthread_cond_t cond; 
 ret = pthread_cond_init(&cond, &attr);
 if (ret != 0) return ret;
 else
   printf("pthread_cond_init: SUCCESS\n");
 
 pthread_cond_destroy(&cond);
 pthread_condattr_destroy(&attr);
 return 0;
}


