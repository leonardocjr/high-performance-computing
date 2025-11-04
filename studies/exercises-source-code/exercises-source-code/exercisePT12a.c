#include <stdio.h>
#include <stdlib.h> // rand_r
#include <unistd.h> // getpid

// note: >= 2GB of integers (each takes 4 bytes) implies compilation with "-mcmodel=medium"
// https://stackoverflow.com/questions/10486116/what-does-this-gcc-error-relocation-truncated-to-fit-mean
// https://gcc.gnu.org/onlinedocs/gcc-7.2.0/gcc/x86-Options.html#index-mcmodel_003dmedium-1

// note: always ensure that NUM_CELLS <= UINT_MAX = 4,294,967,295
// (this is because the loop counters bellow are uint, not ulong)

// 1GB of integers needs 2^28 cells: 2^28 cells x 2^2 bytes/cell = 2^30 bytes = 1GByte
#define NUM_CELLS 268435456

// 2GB of integers needs 2^29 cells; 2^29 cells x 2^2 bytes/cell = 2^31 bytes = 2GBytes
//#define NUM_CELLS 536870912

// 4GB of integers needs 2^30 cells; 2^30 cells x 2^2 bytes/cell = 2^32 bytes = 4GBytes
//#define NUM_CELLS 1073741824

// 8GB of integers needs 2^31 cells; 2^31 cells x 2^2 bytes/cell = 2^33 bytes = 8GBytes
//#define NUM_CELLS 2147483648

unsigned int GLOBAL_vector[NUM_CELLS];

void init_vector()
{
 unsigned int i, myseed=getpid();

 for (i=0; i < NUM_CELLS; i++)
    GLOBAL_vector[i] = rand_r(&myseed);
}

unsigned int count_odds()
{
 unsigned int i, num_odds=0U;

 for (i=0; i < NUM_CELLS; i++)
    if (GLOBAL_vector[i]%2 != 0) num_odds++;

 return(num_odds);
}

int main()
{
    unsigned int num_odds;
    
    init_vector();
    
    num_odds=count_odds();
    
    printf("num_odds = %u (%.3g%%)\n", num_odds, 100.0*(float)num_odds/(float)NUM_CELLS);
}
