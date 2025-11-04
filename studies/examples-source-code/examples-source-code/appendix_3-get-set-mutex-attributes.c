#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

//https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutexattr_gettype.html
//https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutexattr_settype.html
//https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutexattr_getrobust.html
//https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutexattr_setrobust.html
//https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutexattr_getpshared.html
//https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutexattr_setpshared.html
//https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutexattr_getprotocol.html
//https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutexattr_setprotocol.html
//https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutexattr_getprioceiling.html
//https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutexattr_setprioceiling.html

void show_type (int type)
{
 if (type == PTHREAD_MUTEX_DEFAULT)
   printf("type is PTHREAD_MUTEX_DEFAULT\n");
 if (type == PTHREAD_MUTEX_NORMAL)
   printf("type is PTHREAD_MUTEX_NORMAL\n");
 if (type == PTHREAD_MUTEX_ERRORCHECK)
   printf("type is PTHREAD_MUTEX_ERRORCHECK\n");
 if (type == PTHREAD_MUTEX_RECURSIVE)
   printf("type is PTHREAD_MUTEX_RECURSIVE\n");
}

void show_robustness (int robust)
{    	
 if (robust == PTHREAD_MUTEX_STALLED)
   printf("robustness is PTHREAD_MUTEX_STALLED\n");
 else if (robust == PTHREAD_MUTEX_ROBUST)
   printf("robustness is PTHREAD_MUTEX_ROBUST\n");
}

void show_pshared (int pshared)
{    	
 if (pshared == PTHREAD_PROCESS_PRIVATE)
   printf("pshared is PTHREAD_PROCESS_PRIVATE\n");
 else if (pshared == PTHREAD_PROCESS_SHARED)
   printf("pshared is PTHREAD_PROCESS_SHARED\n");
}

void show_protocol (int protocol)
{    	
 if (protocol ==  PTHREAD_PRIO_NONE)
   printf("protocol is PTHREAD_PRIO_NONE\n");
 else if (protocol == PTHREAD_PRIO_INHERIT)
   printf("protocol is PTHREAD_PRIO_INHERIT\n");
 else if (protocol ==  PTHREAD_PRIO_PROTECT)
   printf("protocol is PTHREAD_PRIO_PROTECT\n");
}

void show_prioceiling (int prioceiling)
{    	
 printf("prioceiling is %d\n", prioceiling);
} 

int main ()
{
 pthread_mutexattr_t attr;
 int ret, type, robust, pshared, protocol, prioceiling;

 ret = pthread_mutexattr_init(&attr);
 if (ret != 0) return ret;

 //ret = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
 //if (ret != 0) return ret;
 ret = pthread_mutexattr_gettype(&attr, &type);
 if (ret != 0) return ret; else show_type(type);
        
 //ret = pthread_mutexattr_setrobust(&attr, PTHREAD_MUTEX_ROBUST);
 //if (ret != 0) return ret;
 ret = pthread_mutexattr_getrobust(&attr, &robust);
 if (ret != 0) return ret; else show_robustness(robust);

 //ret = pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
 //if (ret != 0) return ret;
 ret = pthread_mutexattr_getpshared(&attr, &pshared);
 if (ret != 0) return ret; else show_pshared(pshared);

 //ret = pthread_mutexattr_setprotocol(&attr, PTHREAD_PRIO_INHERIT);
 //if (ret != 0) return ret;
 ret = pthread_mutexattr_getprotocol(&attr, &protocol);
 if (ret != 0) return ret; else show_protocol(protocol);

 //ret = pthread_mutexattr_setprioceiling(&attr, 2);
 //if (ret != 0) return ret;
 ret = pthread_mutexattr_getprioceiling(&attr, &prioceiling);
 if (ret != 0) return ret; else show_prioceiling(prioceiling);

 pthread_mutex_t mutex; 
 ret = pthread_mutex_init(&mutex, &attr);
 if (ret != 0) return ret;
 else
   printf("pthread_mutex_init: SUCCESS\n");
 
 pthread_mutex_destroy(&mutex);
 pthread_mutexattr_destroy(&attr);
 return 0;
}


