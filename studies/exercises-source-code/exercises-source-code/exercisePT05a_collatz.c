// check the collatz conjecture

#include <stdio.h>
#include <stdlib.h> // exit, rand_r
#include <sys/types.h> // getpid
#include <unistd.h> // getpid

int main()
{    
 unsigned int seed;
 long p, pbak, steps=0L;
 
 seed=getpid(); // specific seed for this process
 pbak=p=rand_r(&seed);
 
 while (++steps) {
    if (p % 2 == 0) p = p / 2;
    else {
        if ((3*p + 1) < p) {
            printf("OVERFLOW\n");
            exit(1);
        }
        else
            p = 3*p + 1;
    }
    if (p == 1) break;
 }
 
 printf("process %d: initial p=%ld converged in %ld steps\n", getpid(), pbak, steps);
}   
