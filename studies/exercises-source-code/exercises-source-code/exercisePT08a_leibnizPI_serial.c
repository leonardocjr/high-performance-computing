// approximate PI; SERIAL VERSION

#include <stdio.h>
#include <math.h>

#define NUM_TERMS 100000000L

int main ()
{
 unsigned long k;
 double factor=1.0, sum=0.0;
 double approxPI;
 
 for (k=0; k<NUM_TERMS; k++) {
   sum += factor/(2*k+1);
   factor = -factor;
 }
 
 approxPI = 4.0*sum;
 printf("thread main: approx PI = %.20g\n", approxPI);
 printf("thread main: \"true\" PI = %.20g\n", M_PI);
 printf("thread main: abs error = %.20g\n", fabs(M_PI-approxPI)); 
}
