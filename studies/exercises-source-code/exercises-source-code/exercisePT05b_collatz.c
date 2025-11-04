// check the collatz conjecture

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> // rand_r

#define NUM_WORKERS 4

void *aThread(void *arg)
{
 long tid=(long)arg;
 
 unsigned int seed; // specific seed for this thread
 long p, pbak, steps=0L;
 
 seed=pthread_self();
 pbak=p=rand_r(&seed);
 
 while (++steps) {
    if (p % 2 == 0) p = p / 2;
    else {
        if ((3*p + 1) < p) {
            printf("OVERFLOW\n");
            pthread_exit(NULL); 
        }
        else
            p = 3*p + 1;
    }
    if (p == 1) break;
 }
 
 printf("thread %ld (%lu): initial p=%ld converged in %ld steps\n", tid, pthread_self(), pbak, steps);
 
 pthread_exit(NULL); 
}

int main()
{
 pthread_t threads[NUM_WORKERS];
 long t;
   
 for(t=0;t<NUM_WORKERS;t++){
     pthread_create(&threads[t], NULL, aThread, (void *)t);
 }

 pthread_exit(NULL); 
}   
