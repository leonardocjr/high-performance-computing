#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

unsigned long long i=0;

void *aThread(void *arg)
{
   while (++i) pthread_testcancel();
   printf("aThread: ERROR; should never reach this printf\n");
   pthread_exit(NULL);
}

int main()
{
   pthread_t thread; int ret; void *status;

   ret = pthread_create(&thread, NULL, aThread, (void *)NULL);
   if (ret){ printf("ERROR; return code from pthread_create() is %d\n", ret); exit(ret); }

   ret = pthread_cancel(thread);
   if (ret){ printf("ERROR; return code from pthread_cancel() is %d\n", ret); exit(ret); }

   ret = pthread_join(thread, &status);
   if (ret){ printf("ERROR; return code from pthread_join() is %d\n", ret); exit(ret); }
   if (status == PTHREAD_CANCELED) printf("thread main: thread created was cancelled\n");
   else printf("thread main: thread created was not cancelled\n");
   
   printf("thread main: i=%llu\n",i);

   pthread_exit(NULL);
}
