#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 8 // W
#define NUM_TRANSACTIONS 100000000
#define NUM_REGISTERS 2000000

int GLOBAL_transaction=0;
pthread_mutex_t GLOBAL_mutex_transaction=PTHREAD_MUTEX_INITIALIZER;

int GLOBAL_db[NUM_REGISTERS];
pthread_rwlock_t GLOBAL_db_rwlock=PTHREAD_RWLOCK_INITIALIZER; //a: one rw lock
pthread_mutex_t GLOBAL_db_mutex=PTHREAD_MUTEX_INITIALIZER;    //b: one mutex

void *aThread(void *arg)
{
 long tid=(long)arg;
 unsigned int myseed=(unsigned int)tid+1; // ensure reproducibility
 //unsigned int myseed=(unsigned int)pthread_self(); // ensure full randomness
 int transaction, myrandom, register_index;
 unsigned char transaction_type;
 int transactions_per_thread=0;

 while (1) { 
     
    // get a transaction number and finish if all transactions done
    pthread_mutex_lock(&GLOBAL_mutex_transaction);
    transaction=GLOBAL_transaction; GLOBAL_transaction++;
    pthread_mutex_unlock(&GLOBAL_mutex_transaction);
    if (transaction >= NUM_TRANSACTIONS) break;
    transactions_per_thread++;
    
    // get a random number for this transaction
    myrandom=rand_r(&myseed);

    // define the transaction type
    transaction_type=myrandom%100; // 0..97 == read; 98..99 == write
    
    // define the register to access 
    register_index=myrandom%NUM_REGISTERS;
    
    // do transaction
    //pthread_mutex_lock(&GLOBAL_db_mutex); // b
    if (transaction_type < 98) {
        pthread_rwlock_rdlock(&GLOBAL_db_rwlock); // a
        //int register_content = GLOBAL_db[register_index];
        GLOBAL_db[register_index] = GLOBAL_db[register_index];
    }
    else {
        pthread_rwlock_wrlock(&GLOBAL_db_rwlock); // a
        GLOBAL_db[register_index]=1;
    }
    pthread_rwlock_unlock(&GLOBAL_db_rwlock); // a
    //pthread_mutex_unlock(&GLOBAL_db_mutex); // b
 }
 
 printf("thread %ld: ending after %d transactions\n", tid, transactions_per_thread);
 pthread_exit((void*)NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    long t;
          
    // populate the "database"
    for(int i=0; i < NUM_REGISTERS; i++)
        GLOBAL_db[i]=0;
    
    for(t=0;t<NUM_THREADS;t++)
        pthread_create(&threads[t], NULL, aThread, (void *)t);
   
    for(t=0; t<NUM_THREADS; t++)
        pthread_join(threads[t], NULL);
  
    // check probability distribution
    int ones=0;
    for (int i=0; i < NUM_REGISTERS; i++)
        if (GLOBAL_db[i]==1) ones ++;
    printf("percentage of registers changed: %.3g%%\n", ((double)ones/(double)NUM_REGISTERS)*100.0);
        
    pthread_mutex_destroy(&GLOBAL_mutex_transaction);
    pthread_rwlock_destroy(&GLOBAL_db_rwlock); // a
    pthread_mutex_destroy(&GLOBAL_db_mutex); // b
    pthread_exit(NULL);
}
