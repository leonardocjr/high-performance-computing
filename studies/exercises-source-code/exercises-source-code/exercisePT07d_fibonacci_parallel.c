// generate Fibonnaci sequence; PARALLEL VERSION

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define NUM_TERMS 100
#define NUM_WORKERS (4+1) // includes main

unsigned long GLOBAL_fibonacci[NUM_TERMS];

void *aThread(void *arg)
{
 unsigned long tid=(unsigned long)arg;
 unsigned int f;
 unsigned int slice_width, begin, end;

 slice_width=NUM_TERMS/NUM_WORKERS;
 begin= tid*slice_width; end = begin + slice_width - 1;
 printf("thread %lu: begin = %u end = %u\n", tid, begin, end);
 
 for (f=begin; f<=end; f++)
     GLOBAL_fibonacci[f] = (unsigned long)round((pow( (1+sqrt(5))/2, f)) / sqrt(5));
 
 return(NULL);
}

int main()
{
 pthread_t threads[NUM_WORKERS];
 unsigned long t;
 unsigned int slice_remainder, f;
  
 if ((slice_remainder=NUM_TERMS%NUM_WORKERS) != 0) {
	 printf("work slices uneven; exiting\n");
	 exit(1);
 }

 for(t=1;t<NUM_WORKERS;t++)
     pthread_create(&threads[t], NULL, aThread, (void *)t);

 aThread(0);

 for(t=1; t<NUM_WORKERS; t++)
    pthread_join(threads[t], NULL);
 
 /* Show Fibonacci sequence */
 for (f=0; f<NUM_TERMS; f++) 
	printf("%u %lu\n", f, GLOBAL_fibonacci[f]);

 pthread_exit(NULL); 
}
