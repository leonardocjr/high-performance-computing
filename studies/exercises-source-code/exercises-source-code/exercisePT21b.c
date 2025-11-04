#include <stdio.h>
#include <unistd.h> // getpid
#include <stdlib.h> // exit, rand_r
#include <math.h> // sqrt
#include <pthread.h>

#define NUM_CELLS 100000
double GLOBAL_vector[NUM_CELLS];

unsigned int GLOBAL_i=0;
pthread_mutex_t GLOBAL_i_mutex = PTHREAD_MUTEX_INITIALIZER;

#define NUM_THREADS 4
double GLOBAL_sum_distances[NUM_THREADS];

void init_vector()
{
 unsigned int i, myseed=getpid();

 for (i=0; i < NUM_CELLS; i++) {
	GLOBAL_vector[i] = (double)rand_r(&myseed)/(double)(RAND_MAX);
 }
}

void *compute_sum_distances(void *arg)
{
 unsigned long tid=(unsigned long)arg;
 unsigned int i,j;
 double x1, x2, y1, y2, distance=0.0;
  
 while(1) {	 
     pthread_mutex_lock (&GLOBAL_i_mutex);
     i = GLOBAL_i; GLOBAL_i += 2;
     pthread_mutex_unlock (&GLOBAL_i_mutex);
 
     if (i>=NUM_CELLS) break;

     x1 = GLOBAL_vector[i]; y1 = GLOBAL_vector[i+1];
     for (j=i+2; j < NUM_CELLS; j+=2) {
         x2 = GLOBAL_vector[j]; y2 = GLOBAL_vector[j+1];
         distance += sqrt ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
     }
 };

 GLOBAL_sum_distances[tid]=distance;
 return(NULL);
}

int main()
{
 double sum_distances=0,avg_distance;
 unsigned long total_pairs;

 pthread_t threads[NUM_THREADS];
 unsigned long t;

 if (NUM_CELLS % 2 != 0) {
     printf("NUM_CELLS is not even\n"); exit(1);
 }

 init_vector();
	
 for(t=1;t<NUM_THREADS;t++)
     pthread_create(&threads[t], NULL, compute_sum_distances, (void *)t);
        
 compute_sum_distances(0);
 sum_distances=GLOBAL_sum_distances[0];

 for(t=1;t<NUM_THREADS;t++) {
     pthread_join(threads[t],NULL);
     sum_distances += GLOBAL_sum_distances[t];
 }

 total_pairs=(unsigned long)((double)(NUM_CELLS/2)*((double)(NUM_CELLS/2)-1)/2);
 avg_distance=sum_distances/total_pairs;
 printf("%.20g\n", avg_distance);
 //The average distance between two random points within a square of side length \(a\) is approximately \(0.5214a\)
 //https://mindyourdecisions.com/blog/2016/07/03/distance-between-two-random-points-in-a-square-sunday-puzzle/

 pthread_exit(NULL);
}
