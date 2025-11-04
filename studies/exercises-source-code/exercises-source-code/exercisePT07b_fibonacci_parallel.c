// generate Fibonnaci sequence; PARALLEL VERSION

#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define NUM_TERMS 100
#define NUM_WORKERS 4

typedef struct {
    unsigned int begin;
    unsigned int end;
} slice_t;
slice_t GLOBAL_slices[NUM_WORKERS];

unsigned long GLOBAL_fibonacci[NUM_TERMS];

void *aThread(void *arg)
{
 unsigned long tid=(unsigned long)arg;
 unsigned int f;
 
 printf("thread %lu: begin = %u end = %u\n", tid, GLOBAL_slices[tid].begin, GLOBAL_slices[tid].end);
 for (f=GLOBAL_slices[tid].begin; f<=GLOBAL_slices[tid].end; f++)
     GLOBAL_fibonacci[f] = (unsigned long)round((pow( (1+sqrt(5))/2, f)) / sqrt(5));
 
 pthread_exit(NULL);
}

int main()
{
 pthread_t threads[NUM_WORKERS];
 unsigned long t;
 unsigned int slice_width, slice_remainder, f;
  
 slice_width=NUM_TERMS/NUM_WORKERS;
 slice_remainder=NUM_TERMS%NUM_WORKERS;

 for(t=0;t<NUM_WORKERS;t++){

     if (t==0) GLOBAL_slices[0].begin = 0;
     else GLOBAL_slices[t].begin = GLOBAL_slices[t-1].end+1;     

     GLOBAL_slices[t].end = GLOBAL_slices[t].begin + slice_width - 1;
     if (slice_remainder > 0) { GLOBAL_slices[t].end++; slice_remainder --; }

     pthread_create(&threads[t], NULL, aThread, (void *)t);
 }

 for(t=0; t<NUM_WORKERS; t++)
    pthread_join(threads[t], NULL);
 
 /* Show Fibonacci sequence */
 for (f=0; f<NUM_TERMS; f++) 
	printf("%u %lu\n", f, GLOBAL_fibonacci[f]);

 pthread_exit(NULL); 
}
