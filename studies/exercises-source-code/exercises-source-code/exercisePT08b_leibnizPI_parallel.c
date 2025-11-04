// approximate PI; PARALLEL VERSION

#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define NUM_TERMS 100000000L
#define NUM_WORKERS (1+4) // includes main

typedef struct {
    unsigned long begin;
    unsigned long end;
} slice_t;
slice_t GLOBAL_slices[NUM_WORKERS];

double GLOBAL_sum[NUM_WORKERS];

void *aThread(void *arg)
{
 unsigned long tid=(unsigned long)arg;
 unsigned long k;
 double factor = 1.0;
 
 printf("thread %lu: begin = %lu end = %lu\n", tid, GLOBAL_slices[tid].begin, GLOBAL_slices[tid].end);
 if (GLOBAL_slices[tid].begin % 2 != 0) factor = -1.0;
 for (k=GLOBAL_slices[tid].begin; k<=GLOBAL_slices[tid].end; k++) {
   GLOBAL_sum[tid] += factor/(2*k+1);
   factor = -factor;
 }
 
 return(NULL);
}

int main()
{
 pthread_t threads[NUM_WORKERS];
 unsigned long t;
 double approxPI = 0.0;
 unsigned long slice_width, slice_remainder;
 
 slice_width=NUM_TERMS/NUM_WORKERS;
 slice_remainder=NUM_TERMS%NUM_WORKERS;
    
 for(t=0;t<NUM_WORKERS;t++){
     GLOBAL_sum[t]=0.0;
     
     if (t==0) GLOBAL_slices[0].begin = 0;
     else GLOBAL_slices[t].begin = GLOBAL_slices[t-1].end+1;     

     GLOBAL_slices[t].end = GLOBAL_slices[t].begin + slice_width - 1;
     if (slice_remainder > 0) { GLOBAL_slices[t].end++; slice_remainder --; }     

     if (t>0) pthread_create(&threads[t], NULL, aThread, (void *)t);
 }
 
 aThread(0);

 for(t=0; t<NUM_WORKERS; t++) {
    if (t>0) pthread_join(threads[t], NULL);
    approxPI += GLOBAL_sum[t];
 }

 approxPI = 4.0*approxPI;
 printf("thread main: approx PI = %.20g\n", approxPI);	
 printf("thread main: \"true\" PI = %.20g\n", M_PI);	
 printf("thread main: abs error = %.20g\n", fabs(M_PI-approxPI));	
 
 pthread_exit(NULL); 
}
