#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 8 // W
#define NUM_TRANSACTIONS 100000000
#define NUM_REGISTERS 2000000

int GLOBAL_transaction=0;
pthread_mutex_t GLOBAL_mutex_transaction=PTHREAD_MUTEX_INITIALIZER;

int GLOBAL_db[NUM_REGISTERS];
pthread_rwlock_t GLOBAL_db_rwlock[NUM_THREADS];  //a: W rw locks
pthread_mutex_t GLOBAL_db_mutex[NUM_THREADS];    //b: W mutexes

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
    //pthread_mutex_lock(&GLOBAL_db_mutex[register_index%NUM_THREADS]); // b
    if (transaction_type < 98) {
        pthread_rwlock_rdlock(&GLOBAL_db_rwlock[register_index%NUM_THREADS]); // a
        //int register_content = GLOBAL_db[register_index];
        GLOBAL_db[register_index] = GLOBAL_db[register_index];
    }
    else {
        pthread_rwlock_wrlock(&GLOBAL_db_rwlock[register_index%NUM_THREADS]); // a
        GLOBAL_db[register_index]=1;
    }
    pthread_rwlock_unlock(&GLOBAL_db_rwlock[register_index%NUM_THREADS]); // a
    //pthread_mutex_unlock(&GLOBAL_db_mutex[register_index%NUM_THREADS]); // b
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

    // initialize rwlocks (a) or mutexes (b)
    for(t=0; t<NUM_THREADS; t++) {
        pthread_rwlock_init(&GLOBAL_db_rwlock[t], NULL); // a
        pthread_mutex_init(&GLOBAL_db_mutex[t], NULL); // b
    }
    
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

    // destroy rwlocks (a) or mutexes (b)
    for(t=0; t<NUM_THREADS; t++) {
	pthread_rwlock_destroy(&GLOBAL_db_rwlock[t]); // a
        pthread_mutex_destroy(&GLOBAL_db_mutex[t]); // b
    }
    pthread_exit(NULL);
}
