/*
Question - Implement producer and consumer using condition variable and mutex
*/

#include <stdio.h>
#include <pthread.h>
#include <string.h> // for memset
#include <stdint.h>
#include <assert.h>
#include <unistd.h> // for sleep

#define BUFFER_MAX 10

struct buffer
{
  pthread_mutex_t lock;
  pthread_cond_t more_items;
  pthread_cond_t more_space;
  int data[BUFFER_MAX];
  int nextin;
  int nextout;
  int empty;
};

struct buffer buff;

/*
#define IS_FULL(buff) \
  ((buff.head == buff.tail) && (buff.count == BUFFER_MAX))

#define IS_EMPTY(buff) \
  ((buff.head == buff.tail) && (buff.count == 0))
*/

void circular_buffer_init(void)
{
  memset(&buff, 0, sizeof(struct buffer));
  buff.nextin = 0;
  buff.nextout = 0;
  buff.empty = BUFFER_MAX;
}
void* producer(void* arg)
{
  //uint8_t id = *((uint8_t*)arg);
  static int num = 0;

  printf("\nProducer thread %d started with nextin%d nextout%d empty%d",
    0, buff.nextin, buff.nextout, buff.empty);
  pthread_mutex_lock(&buff.lock);
  while(1)
  {
    if((buff.nextin == buff.nextout) && (buff.empty == 0))
    {
      printf("\nError - Buffer full");
      pthread_cond_wait(&buff.more_space, &buff.lock);
    }

    buff.data[buff.nextin] = ++num;
    if (++buff.nextin == BUFFER_MAX)
    {
      buff.nextin = 0;
    }
    buff.empty--;

    pthread_cond_signal(&buff.more_items);
    pthread_mutex_unlock(&buff.lock);
    printf("\nProduced %d nextin %d, nextout %d empty %d",
      num, buff.nextin, buff.nextout, buff.empty);
    sleep(1);
  }
  printf("\nProducer Thread EXIT");
}

void* consumer (void* arg)
{
  //uint8_t id = *((uint8_t*)arg);
  uint8_t item = 0;

  printf("\nConsumer thread %d started with nextin%d nextout%d empty%d",
    1, buff.nextin, buff.nextout, buff.empty);

  pthread_mutex_lock(&buff.lock);
  while(1)
  {
    if ((buff.nextin == buff.nextout) && (buff.empty == BUFFER_MAX))
    {
      printf("\nError - Buffer is empty - wait on more space");
      pthread_cond_wait(&buff.more_items, &buff.lock);
    }
    item = buff.data[buff.nextout];
    buff.empty++;

    if (++buff.nextout == BUFFER_MAX)
    {
      buff.nextout = 0;
    }
    pthread_cond_signal(&buff.more_space);
    pthread_mutex_unlock(&buff.lock);
    printf("\nConsumed %d nextin %d  nextout %d empty %d", 
      item, buff.nextin, buff.nextout, buff.empty); 
    sleep(2);
  }

  printf("\nConsumer Thread EXIT");
}

int main()
{
  int error = 0;
  pthread_t tid1, tid2;

  printf("\nInit Circular buffer");
  circular_buffer_init();

  printf("\nInit mutex");
  error = pthread_mutex_init(&buff.lock, NULL);
  assert(!error);

  printf("\nCreating threads");
  pthread_create(&tid1, NULL, &producer, NULL);
  //assert(!error);
  pthread_create(&tid2, NULL, &consumer, NULL);
  //assert(!error);

  printf("\nWaiting for threads to finish");
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  printf("\nDestroying mutex");
  pthread_mutex_destroy(&buff.lock);

  return 0;
}

