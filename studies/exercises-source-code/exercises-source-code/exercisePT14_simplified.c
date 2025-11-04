#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> // exit
#include <stdint.h> // uintptr_t (avoid -Wpointer-to-int-cast,-Wint-to-pointer-cast warnings)


// 1GB of integers needs 2^28 cells: 2^28 cells x 2^2 bytes/cell = 2^30 bytes = 1GByte
//#define NUM_CELLS 268435456
#define NUM_CELLS 5

unsigned int GLOBAL_vector1[NUM_CELLS];
unsigned int GLOBAL_vector2[NUM_CELLS];

#define NUM_THREADS 8

typedef struct {
  int begin;
  int end;
} slice_t;
slice_t GLOBAL_slices[NUM_THREADS];

void init_vector(unsigned int *vect, unsigned int val)
{
 int i;

 for (i=0; i < NUM_CELLS; i++)
    vect[i]=val;
}

void *aThread(void *arg)
{
 long tid=(long)arg; unsigned int dot_product=0;

 for (int i=GLOBAL_slices[tid].begin; i <= GLOBAL_slices[tid].end; i++)
    dot_product += GLOBAL_vector1[i] * GLOBAL_vector2[i];

 pthread_exit((void*)(uintptr_t)dot_product); 
}

int main()
{    
    pthread_t threads[NUM_THREADS];
    unsigned long t, slice_width, slice_remainder;
    unsigned int dot_product=0;
    void *retval;
    
    init_vector(GLOBAL_vector1, 1);
    init_vector(GLOBAL_vector2, 2);
    
    slice_width = NUM_CELLS / NUM_THREADS;
    slice_remainder=NUM_CELLS%NUM_THREADS;

    for(t=0;t<NUM_THREADS;t++){
        
		// this always works, irregardless of n>=w or n<w	
        if (t==0) GLOBAL_slices[0].begin = 0;
		else GLOBAL_slices[t].begin = GLOBAL_slices[t-1].end+1;
		GLOBAL_slices[t].end = GLOBAL_slices[t].begin + slice_width - 1;
		if (slice_remainder > 0) { GLOBAL_slices[t].end++; slice_remainder --; }

        printf("thread main: t = %ld, begin = %d, end = %d\n", t, GLOBAL_slices[t].begin, GLOBAL_slices[t].end);
        pthread_create(&threads[t], NULL, aThread, (void *)t);
    }
    
    for(t=0; t<NUM_THREADS; t++) {
        pthread_join(threads[t], &retval);
        dot_product += (unsigned int)(uintptr_t)retval;
    }
    
    printf("dot_product = %u\n", dot_product);
    pthread_exit(NULL);
}   
