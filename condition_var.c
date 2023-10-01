/*
@TODO - Call pthread_cond_wait in while loop because threads can come out of it
even without the condition being true.

//SETUP - 
int pthread_cond_init(pthread_cond_t *cvp, pthread_condattr_t *attrp)
int pthread_cond_destroy(pthread_cond_t *cvp)
int pthread_condattr_init(pthread_condattr_t *attrp)
int pthread_condattr_destroy(pthread_condattr_t *attrp)

// Lock mutex before calling cond_wait
pthread_mutex_lock(&mutex)
pthread_cond_wait(&cond_var, &mutex)
// All threads wait here in queue. This function releases mutex and put the thread
// to sleep and in queue. All in single atomic step

// These threads are released in response to calls to 
pthread_cond_signal () - releases 1st thread in line
pthread_cond_broadcast(&cond_var);
//releases all threads. However before a thread may return from cond_wait, it first relocks //the mutex. Thus only one thread at a time actually
// returns form cond_wait.

//Weird stuff- A thread maybe released from condition variable at any moment (maybe //spontaneously). Hence, adter cond_wait returns, caller should check to make sure we 
//should have returned.

// ALLOWS MULTIPLE PRODUCERS AND CONSUMERS
Use 2 cond var - more_space, more_items
1 mutex
2 locations - nextin, nextout
1 buffer

*/

#include <pthread.h>
/* for NULL */
#include <stddef.h>
#include <stdio.h>
#include <unistd.h> /* For sleep() */

#define BUFF_SIZE 10

// TIP - pthreat create takes void* ()(void*)
void* consumer_cond (void*);
void* producer_cond (void*);

struct buffer
{
  pthread_mutex_t lock;
  pthread_cond_t more_space;
  pthread_cond_t more_items;
  int nextin;
  int nextout;
  int empty;
  int buffer[BUFF_SIZE];
};

struct buffer buffer1;

void* producer_cond (void* arg )
{
  int item = 0;
  static int count = 0;
  while(1)
  {
    printf("PRODUCER\n");
    pthread_mutex_lock(&buffer1.lock);
    printf("PRODUCER got MUTEX\n");
    if (buffer1.empty == 0)
    {
      // If number of empty spaces is 0 - then wait
      printf("PRODUCER in QUEUE\n");
      pthread_cond_wait(&buffer1.more_space, &buffer1.lock);
    }
    else
    {
      printf("PRODUCER: Empty space = %d Enter item:\n", buffer1.empty);
    }
    // Released from cond_wait as a result of something got consumed - Locked mutex again
    //scanf("%d", &item);
    item = 65+ count++;
    buffer1.buffer[buffer1.nextin++] = item;

    if (buffer1.nextin == BUFF_SIZE)
      buffer1.nextin = 0;

    buffer1.empty--;
    //sleep(1);
    printf("PRODUCER: Signalling consumer of more items\n");
    pthread_cond_signal(&buffer1.more_items);
    pthread_mutex_unlock (&buffer1.lock);
  }
}

void* producer_cond2 (void* arg)
{
  int item = 0;
  static int count = 0;

  while(1)
  {
    printf("PRODUCER2\n");
    pthread_mutex_lock(&buffer1.lock);
    printf("PRODUCER2 got MUTEX\n");
    if (buffer1.empty == 0)
    {
      // If number of empty spaces is 0 - then wait
      printf("PRODUCER2 in QUEUE\n");
      pthread_cond_wait(&buffer1.more_space, &buffer1.lock);
    }
    else
    {
      printf("PRODUCER2: Empty space = %d Enter item:\n", buffer1.empty);
    }
    // Released from cond_wait as a result of something got consumed - Locked mutex again
    //scanf("%d", &item);
    item = 65+count++;
    buffer1.buffer[buffer1.nextin++] = item;

    if (buffer1.nextin == BUFF_SIZE)
      buffer1.nextin = 0;

    buffer1.empty--;
    //sleep(1);
    printf("PRODUCER2: Signalling consumer of more items\n");
    pthread_cond_signal(&buffer1.more_items);
    pthread_mutex_unlock (&buffer1.lock);
  }
}

void* consumer_cond (void* arg)
{
  while (1)
  {
    printf("CONSUMER\n");
    pthread_mutex_lock(&buffer1.lock);
    printf("CONSUMER got MUTEX\n");
    if (buffer1.empty == BUFF_SIZE)
    {
      // If number of empty spaces is BUFF_SIZE - meaning nothing to consume
      printf("CONSUMER in QUEUE\n");
      pthread_cond_wait(&buffer1.more_items, &buffer1.lock);   
    }
   // sleep(2);
    printf("CONSUMER Consumed %d\n", buffer1.buffer[buffer1.nextout++]);
    if (buffer1.nextout == BUFF_SIZE)
      buffer1.nextout = 0; 
 
    buffer1.empty++;
    printf("CONSUMER:Signalling producer of more space\n");
    pthread_cond_signal(&buffer1.more_space);
    pthread_mutex_unlock (&buffer1.lock);
  }
}

void* consumer_cond2 (void* arg)
{
  while (1)
  {
    printf("CONSUMER2\n");
    pthread_mutex_lock(&buffer1.lock);
    printf("CONSUMER2 got MUTEX\n");
    if (buffer1.empty == BUFF_SIZE)
    {
      // If number of empty spaces is BUFF_SIZE - meaning nothing to consume
      printf("CONSUMER2 in QUEUE\n");
      pthread_cond_wait(&buffer1.more_items, &buffer1.lock);   
    }
    //sleep(2);
    printf("CONSUMER2 Consumed %d\n", buffer1.buffer[buffer1.nextout++]);
    if (buffer1.nextout == BUFF_SIZE)
      buffer1.nextout = 0; 
 
    buffer1.empty++;
    printf("CONSUMER2 Signalling producer of more space\n");
    pthread_cond_signal(&buffer1.more_space);
    pthread_mutex_unlock (&buffer1.lock);
  }
}

int main(void)
{
  /* Dont forget to use pthread join if you use tid as local variables coz you dont
  want the program to return and local variables are deinit */
  printf("\n\n == CONDITION VARIABLE == \n\n");
  pthread_t tid1, tid2, tid3, tid4;
  pthread_cond_init (&buffer1.more_space, NULL);
  pthread_cond_init (&buffer1.more_items, NULL);
  //buffer1.lock = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_init (&buffer1.lock, NULL);
  buffer1.nextin = 0;
  buffer1.nextout = 0;
  buffer1.empty = BUFF_SIZE;

  

  // Don't forget the &
  pthread_create (&tid1, NULL, &producer_cond, NULL);
  pthread_create (&tid2, NULL, &consumer_cond, NULL);
  pthread_create (&tid3, NULL, &producer_cond2, NULL);
  pthread_create (&tid4, NULL, &consumer_cond2, NULL);

  // DONT USE & - will give segmentation fault
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);
  pthread_join(tid4, NULL);

  return 0;
}
