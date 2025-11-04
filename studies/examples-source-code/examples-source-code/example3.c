#include <stdio.h>
#include <pthread.h>

pthread_t thread;

void *aThread(void *arg) {	
 printf("another thread: my thread opaque ID: %lu\n", pthread_self());
 if (pthread_equal(pthread_self(), thread))
     printf("SUCCESS: threads are the same, which is correct.\n");
 else
     printf("ERROR: threads are not the same, which is incorrect.\n");
 pthread_exit(NULL);
}

int main()
{
 pthread_create(&thread, NULL, aThread, NULL);
 printf("main thread: my thread opaque ID: %lu\n", pthread_self());
 if (pthread_equal(pthread_self(), thread))
     printf("ERROR: threads are the same, which is incorrect.\n");
 else
     printf("SUCCESS: threads are not the same, which is correct.\n"); 
 pthread_exit(NULL);
}
