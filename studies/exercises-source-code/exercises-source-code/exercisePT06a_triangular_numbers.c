// generate sequence of triangular numbers; PARALLEL VERSION

#include <stdio.h>
#include <pthread.h>

#define NUM_TERMS 100
#define NUM_WORKERS 4

typedef struct {
    unsigned int begin;
    unsigned int end;
} slice_t;
slice_t GLOBAL_slices[NUM_WORKERS];

unsigned long GLOBAL_triangulars[NUM_TERMS];

void *aThread(void *arg)
{
 unsigned long tid=(unsigned long)arg;
 unsigned int n;
 
 printf("thread %lu: begin = %u end = %u\n", tid, GLOBAL_slices[tid].begin, GLOBAL_slices[tid].end);
 for (n=GLOBAL_slices[tid].begin; n<=GLOBAL_slices[tid].end; n++)
     GLOBAL_triangulars[n] = n*(n+1)/2;
 
 pthread_exit(NULL);
}

int main()
{
 pthread_t threads[NUM_WORKERS];
 unsigned long t;
 unsigned int slice_width, n;
  
 slice_width=NUM_TERMS/NUM_WORKERS;
 
 /* Create the worker threads */
 for(t=0;t<NUM_WORKERS;t++){
	 
     GLOBAL_slices[t].begin=t*slice_width;
     
     if (t == NUM_WORKERS -1) GLOBAL_slices[t].end = NUM_TERMS-1;
     else GLOBAL_slices[t].end=GLOBAL_slices[t].begin+slice_width-1;
     
     pthread_create(&threads[t], NULL, aThread, (void *)t);
 }

 /* Wait for the worker threads */
 for(t=0; t<NUM_WORKERS; t++)
    pthread_join(threads[t], NULL);
 
 /* Show triangular sequence */
 for (n=0; n<NUM_TERMS; n++) 
	printf("%u %lu\n", n, GLOBAL_triangulars[n]);

 pthread_exit(NULL); 
}
