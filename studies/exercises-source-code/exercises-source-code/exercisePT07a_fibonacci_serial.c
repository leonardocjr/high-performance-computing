// generate Fibonnaci sequence; SERIAL VERSION

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 100
 
int main()
{
 unsigned long F_current, F_previous = 1, F_previous_previous = 0, F_binet;
 unsigned int f;
 
 printf("n\tRecurrence\tBinet\n");
 printf("0\t0\t%lu\n", (unsigned long)round((pow((1+sqrt(5))/2, f=0)) / sqrt(5)));
 printf("1\t1\t%lu\n", (unsigned long)round((pow((1+sqrt(5))/2, f=1)) / sqrt(5)));
 
 for (f=2; f<N; f++) {
	 F_current = F_previous + F_previous_previous;	 
	 F_binet = (unsigned long)round ((pow((1+sqrt(5))/2, f)) / sqrt(5));
	 printf("%u\t%lu\t%lu\n", f, F_current, F_binet);
	 if (F_current < F_previous) { printf("overflow\n"); exit(1); }
	 if (F_current != F_binet) { printf("mismatch\n"); exit(2); }
	 F_previous_previous = F_previous;
	 F_previous = F_current;
 }
} 
