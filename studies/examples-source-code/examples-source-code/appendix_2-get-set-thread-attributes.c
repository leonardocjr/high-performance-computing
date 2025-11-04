#include <stdio.h>
#include <pthread.h>
#include <limits.h> // PTHREAD_STACK_MIN
#include <stdlib.h>
#include <errno.h> // EINVAL/ENOSTUP 
#include <unistd.h> // getpagesize

// man 3posix pthread_attr_get*/set*

void show_detachstate (int detachstate)
{
 if (detachstate == PTHREAD_CREATE_JOINABLE)
   printf("detachstate is PTHREAD_CREATE_JOINABLE\n");
 else if (detachstate == PTHREAD_CREATE_DETACHED)
   printf("detachstate is PTHREAD_CREATE_DETACHED\n");
}

void show_schedpolicy (int schedpolicy)
{
 if (schedpolicy == SCHED_OTHER)
   printf("schedpolicy is SCHED_OTHER\n");
 else if (schedpolicy == SCHED_FIFO)
   printf("schedpolicy is SCHED_FIFO\n");
 else if (schedpolicy == SCHED_RR)
   printf("schedpolicy is SCHED_RR\n");
}

void show_inheritsched (int inheritsched)
{
 if (inheritsched == PTHREAD_INHERIT_SCHED)
   printf("inheritsched is PTHREAD_INHERIT_SCHED\n");
 else if (inheritsched == PTHREAD_EXPLICIT_SCHED)
   printf("inheritsched is PTHREAD_EXPLICIT_SCHED\n");
}

void show_contentionscope (int contentionscope)
{
 if (contentionscope == PTHREAD_SCOPE_SYSTEM)
   printf("contentionscope is PTHREAD_SCOPE_SYSTEM\n");
 else if (contentionscope == PTHREAD_SCOPE_PROCESS)
   printf("contentionscope is PTHREAD_SCOPE_PROCESS\n");
}

void show_stack (void *stackaddr, size_t stacksize)
{
 printf("stackaddr: %p\t stacksize: %lu\n", stackaddr, stacksize);
}

void show_guardsize (size_t guardsize)
{
 printf("guardsize: %lu\n", guardsize);
}

int main ()
{
 pthread_attr_t attr;
 int ret, detachstate, schedpolicy, inheritsched, contentionscope;
 size_t stacksize_set; void *stackaddr_set;
 size_t stacksize_get; void *stackaddr_get;
 size_t guardsize;
 
 ret = pthread_attr_init(&attr);
 if (ret != 0) return ret;
  
 //ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
 //if (ret != 0) return ret;
 ret = pthread_attr_getdetachstate(&attr, &detachstate);
 if (ret != 0) return ret; else show_detachstate(detachstate);
 
 //ret = pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
 //if (ret != 0) return ret;
 ret = pthread_attr_getschedpolicy(&attr, &schedpolicy);
 if (ret != 0) return ret; else show_schedpolicy(schedpolicy);
 
 //ret = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
 //if (ret != 0) return ret;
 ret = pthread_attr_getinheritsched(&attr, &inheritsched);
 if (ret != 0) return ret; else show_inheritsched(inheritsched); 
 
 //ret = pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
 //if (ret != 0) return ret; // EINVAL/ENOSTUP error: unsupported
 ret = pthread_attr_getscope(&attr, &contentionscope);
 if (ret != 0) return ret; else show_contentionscope(contentionscope); 
 
 //stacksize_set=PTHREAD_STACK_MIN;
 //stackaddr_set=(void*)malloc(stacksize_set);
 //ret = pthread_attr_setstack(&attr, stackaddr_set, stacksize_set);
 //if (ret != 0) return ret;
 ret = pthread_attr_getstack(&attr, &stackaddr_get, &stacksize_get);
 if (ret != 0) return ret; else show_stack(stackaddr_get, stacksize_get); 
 
 //guardsize = 2*getpagesize();
 //ret = pthread_attr_setguardsize(&attr, guardsize);
 //if (ret != 0) return ret; 
 ret = pthread_attr_getguardsize(&attr, &guardsize);
 if (ret != 0) return ret; else show_guardsize(guardsize); 
 
 pthread_attr_destroy(&attr);
 //free(stackaddr_set);
 return 0;
}


