#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void show_pshared (int pshared)
{    	
 if (pshared == PTHREAD_PROCESS_PRIVATE)
   printf("pshared is PTHREAD_PROCESS_PRIVATE\n");
 else if (pshared == PTHREAD_PROCESS_SHARED)
   printf("pshared is PTHREAD_PROCESS_SHARED\n");
}

int main ()
{
 pthread_barrierattr_t attr;
 int ret, pshared;

 ret = pthread_barrierattr_init(&attr);
 if (ret != 0) return ret;

 //ret = pthread_barrierattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
 //if (ret != 0) return ret;
 ret = pthread_barrierattr_getpshared(&attr, &pshared);
 if (ret != 0) return ret; else show_pshared(pshared);

 pthread_barrier_t barrier;
 ret = pthread_barrier_init(&barrier, &attr, 1);
 if (ret != 0) return ret;
 else printf("pthread_barrier_init: SUCCESS\n");
 
 pthread_barrier_destroy(&barrier);
 pthread_barrierattr_destroy(&attr);
 return 0;
}
