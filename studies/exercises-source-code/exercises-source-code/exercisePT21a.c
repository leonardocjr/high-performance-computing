#include <stdio.h>
#include <unistd.h> // getpid
#include <stdlib.h> // exit, rand_r
#include <math.h> // sqrt

#define NUM_CELLS 100000
double GLOBAL_vector[NUM_CELLS];

void init_vector()
{
 unsigned int i, myseed=getpid();

 for (i=0; i < NUM_CELLS; i++) {
	GLOBAL_vector[i] = (double)rand_r(&myseed)/(double)(RAND_MAX);
 }
}

double compute_sum_distances()
{
 unsigned int i,j;
 double x1, x2, y1, y2, distance=0.0;
 
 for (i=0; i < NUM_CELLS; i+=2) {
     x1 = GLOBAL_vector[i]; y1 = GLOBAL_vector[i+1];
     for (j=i+2; j < NUM_CELLS; j+=2) {
         x2 = GLOBAL_vector[j]; y2 = GLOBAL_vector[j+1];
         distance += sqrt ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
     }
 }
 return(distance);
}

int main()
{
 double sum_distances, avg_distance;
 unsigned long total_pairs;

 if (NUM_CELLS % 2 != 0) {
     printf("NUM_CELLS is not even\n"); exit(1);
 }

 init_vector();
 sum_distances=compute_sum_distances();
 total_pairs=(unsigned long)((double)(NUM_CELLS/2)*((double)(NUM_CELLS/2)-1)/2);
 avg_distance=sum_distances/total_pairs;
 printf("%.20g\n", avg_distance);
 //The average distance between two random points within a square of side length \(a\) is approximately \(0.5214a\)
 //https://mindyourdecisions.com/blog/2016/07/03/distance-between-two-random-points-in-a-square-sunday-puzzle/

 return 0;
}
