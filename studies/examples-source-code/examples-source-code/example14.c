#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS  3
#define COUNT_INCREMENTS 10
#define COUNT_LIMIT 12

int count = 0;
pthread_mutex_t count_mutex;
pthread_cond_t count_cond;

void *add_1(void *t) 
{
  int i;
  long my_id = (long)t;

  printf("add_1(): thread %ld, Starting\n", my_id);

  for (i=0; i < COUNT_INCREMENTS; i++) {
    pthread_mutex_lock(&count_mutex);
    count++;
    printf("add_1(): thread %ld, count = %d\n", my_id, count);

    //Check the value of count and signal waiting thread when condition
    //is reached. Note that this occurs while mutex is locked.
    if (count == COUNT_LIMIT) {
      printf("add_1(): thread %ld, count = %d, Threshold reached\n", my_id, count);
      pthread_cond_signal(&count_cond);
      printf("add_1(): thread %ld, Just sent signal\n",my_id);
    }
    pthread_mutex_unlock(&count_mutex);

    // Simulate some work so threads can alternate on mutex lock
    sleep(1);
  }
  
  printf("add_1(): thread %ld, Ending\n", my_id);
  pthread_exit(NULL);
}

void *add_100(void *t) 
{
  long my_id = (long)t;

  printf("add_100(): thread %ld, Starting\n", my_id);

  // Lock mutex and wait for signal. pthread_cond_wait will automatically
  // and atomically unlock mutex and wait. In case COUNT_LIMIT is reached 
  // before this routine is run by the waiting thread, the loop will be 
  // skipped to prevent pthread_cond_wait from being called and never return.
  pthread_mutex_lock(&count_mutex);
  while (count < COUNT_LIMIT) {
    printf("add_100(): thread %ld, count = %d, Going into wait...\n", my_id,count);
    pthread_cond_wait(&count_cond, &count_mutex);
    printf("add_100(): thread %ld, Condition signal received, count = %d\n", my_id,count);
  }
  printf("add_100(): thread %ld, Updating the value of count...\n", my_id);
  count += 100;
  printf("add_100(): thread %ld, count now = %d\n", my_id, count);
  printf("add_100(): thread %ld Unlocking mutex\n", my_id);
  pthread_mutex_unlock(&count_mutex);
  
  printf("add_100(): thread %ld, Ending\n", my_id);
  pthread_exit(NULL);
}

int main()
{
  pthread_t threads[3];

  /* Initialize mutex and condition variable objects */
  pthread_mutex_init(&count_mutex, NULL);
  pthread_cond_init (&count_cond, NULL);

  pthread_create(&threads[0], NULL, add_100, (void *)1);
  pthread_create(&threads[1], NULL, add_1, (void *)2);
  pthread_create(&threads[2], NULL, add_1, (void *)3);

  /* Wait for all threads to complete */
  for (int i = 0; i < NUM_THREADS; i++)
    pthread_join(threads[i], NULL);
  printf ("Main(): Waited and joined with %d threads. Final value of count = %d. Done.\n", NUM_THREADS, count);

  /* Clean up and exit */
  pthread_mutex_destroy(&count_mutex);
  pthread_cond_destroy(&count_cond);
  pthread_exit (NULL);
}
