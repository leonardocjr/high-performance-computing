// guess a random number

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // getpid
#include <pthread.h>
#define NUM_THREADS 8
#define MAX_RANDOM 1000000000
// cannot be more than RAND_MAX ( = 2^31-1 = 2147483647 )

int GLOBAL_number;
pthread_t GLOBAL_threads[NUM_THREADS];
char GLOBAL_guessed[NUM_THREADS]; // 0 = not guessed; 1 = guessed

void *aThread(void *arg)
{
 long tid=(long)arg;
 //unsigned int myseed=(unsigned int)tid+1; // ensure reproducibility
 unsigned int myseed=(unsigned int)pthread_self(); // ensure full randomness
 int number; unsigned int tries=0;

 //while (1) {
 while (++tries) {     
    //number=rand_r(&myseed)%MAX_RANDOM;
    number=rand_r(&myseed);
    
    //printf("Thread %ld: %u\n", tid, number);
    if (number == GLOBAL_number) break; 
 }
 
 // I guessed
 printf("Thread %ld: guessed after %u tries\n", tid, tries);
 GLOBAL_guessed[tid]=1;
 
 // Cancell all other co-worker threads
 for(int t=0;t<NUM_THREADS;t++) {
   // Make sure co-worker thread was already created
   while (GLOBAL_threads[t]==-1);

   // Cancel thread if it is not myself
   if (t!=tid) pthread_cancel(GLOBAL_threads[t]);
 }

 pthread_exit(NULL);
}

int main()
{
   long t; int ret;
   unsigned int myseed;
   void *status;
   
   //myseed=0; // ensure reproducibility
   myseed=getpid(); // ensure full randomness
   //GLOBAL_number=rand_r(&myseed)%MAX_RANDOM;
   GLOBAL_number=rand_r(&myseed);   
   printf("thread main: number to guess is %d\n", GLOBAL_number);
   
   for(t=0;t<NUM_THREADS;t++) {
     GLOBAL_threads[t]=-1;
     GLOBAL_guessed[t]=0;
   }
    
   for(t=0;t<NUM_THREADS;t++){
     ret = pthread_create(&GLOBAL_threads[t], NULL, aThread, (void *)t);
     if (ret){
       printf("ERROR; return code from pthread_create() is %d\n", ret);
       exit(ret);
     }
   }
   
   for(t=0; t<NUM_THREADS; t++) {
     ret = pthread_join(GLOBAL_threads[t], &status);
     if (ret) {
       printf("ERROR; return code from pthread_join() is %d\n", ret);
       exit(ret);
     }
     if (status == PTHREAD_CANCELED)
        printf("thread main: thread %ld was canceled\n", t);
     if (GLOBAL_guessed[t])
        printf("thread main: thread %ld guessed\n", t);	 
   }
 
   printf("thread main: program completed: exiting\n");
   pthread_exit(NULL);
}
