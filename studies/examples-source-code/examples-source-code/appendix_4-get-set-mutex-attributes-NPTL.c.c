#include <stdio.h>
// to access NPTL non-portbable features
#define __USE_GNU
#include <pthread.h>

void show_type (int type)
{
 if (type == PTHREAD_MUTEX_FAST_NP)
   printf("type is PTHREAD_MUTEX_FAST_NP\n");
 if (type == PTHREAD_MUTEX_TIMED_NP)
   printf("type is PTHREAD_MUTEX_TIMED_NP\n");
 if (type == PTHREAD_MUTEX_ERRORCHECK_NP)
   printf("type is PTHREAD_MUTEX_ERRORCHECK_NP\n");
 if (type == PTHREAD_MUTEX_RECURSIVE_NP)
   printf("type is PTHREAD_MUTEX_RECURSIVE_NP\n");
 if (type == PTHREAD_MUTEX_ADAPTIVE_NP)
   printf("type is PTHREAD_MUTEX_ADAPTIVE_NP\n");   
}

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;     // POSIX and NPTL
pthread_mutex_t mutex2 = PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP; // NPTL
pthread_mutex_t mutex3 = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;  // NPTL
pthread_mutex_t mutex4 = PTHREAD_ADAPTIVE_MUTEX_INITIALIZER_NP;   // NPTL

int main ()
{
 pthread_mutexattr_t attr;
 int ret, type;
    
 ret = pthread_mutexattr_init(&attr);
 if (ret != 0) return ret;
 
 ret = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_FAST_NP);
 if (ret != 0) return ret;
 ret = pthread_mutexattr_gettype(&attr, &type);
 if (ret != 0) return ret; else show_type(type);
 
 ret = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_TIMED_NP);
 if (ret != 0) return ret;
 ret = pthread_mutexattr_gettype(&attr, &type);
 if (ret != 0) return ret; else show_type(type);
 
 ret = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK_NP);
 if (ret != 0) return ret;
 ret = pthread_mutexattr_gettype(&attr, &type);
 if (ret != 0) return ret; else show_type(type);
 
 ret = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
 if (ret != 0) return ret;
 ret = pthread_mutexattr_gettype(&attr, &type);
 if (ret != 0) return ret; else show_type(type);
 
 ret = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ADAPTIVE_NP);
 if (ret != 0) return ret;
 ret = pthread_mutexattr_gettype(&attr, &type);
 if (ret != 0) return ret; else show_type(type);
  
 pthread_mutex_t mutex; 
 ret = pthread_mutex_init(&mutex, &attr);
 if (ret != 0) return ret;
 else
   printf("pthread_mutex_init: SUCCESS\n");
 
 pthread_mutex_destroy(&mutex);
 pthread_mutexattr_destroy(&attr);
 return 0;
}


