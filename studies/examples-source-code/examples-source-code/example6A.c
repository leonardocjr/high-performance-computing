#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *aThread(void *arg)
{
   for (int i=0; i<5; i++) { printf("thread created: %d\n", i); sleep(1); }
   printf("thread created: going to self terminate\n");
   pthread_exit(NULL);
}

int main()
{
   pthread_t thread; int ret; void *status;

   ret = pthread_create(&thread, NULL, aThread, (void *)NULL);
   if (ret){ printf("ERROR; return code from pthread_create() is %d\n", ret); exit(ret); }

   for (int i=0; i<2; i++) { printf("thread main: %d\n", i); sleep(1); }

   //ret = pthread_cancel(thread);
   //if (ret){ printf("ERROR; return code from pthread_cancel() is %d\n", ret); exit(ret); }

   ret = pthread_join(thread, &status);
   if (ret){ printf("ERROR; return code from pthread_join() is %d\n", ret); exit(ret); }
   if (status == PTHREAD_CANCELED) printf("thread main: thread created was cancelled\n");
   else printf("thread main: thread created was not cancelled\n");

   pthread_exit(NULL);
}
