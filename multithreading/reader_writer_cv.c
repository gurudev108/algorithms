/*
Implemented using condition variables
Any number of reader threads can read data
When writer thread gets the lock, it should be exclusive

Design -
Improved reader writer where writer has higher priority
2 Condition variables - readerQ, writerQ
readers
writers
activewriters
mutex


*/

#include <stdio.h>
#include <pthread.h>
#include <stddef.h>
#include <assert.h>

#define NUM_MAX_THREADS 5
#define MAX_DATA 10

struct
{
  pthread_mutex_t lock;
  pthread_cond_t readersQ;
  pthread_cond_t writersQ;
  int readers;
  int writers;
  int active_writers;
  char buffer[MAX_DATA];
} data;

void reader (void)
{
  printf("[READER]\n");

  pthread_mutex_lock (&data.lock);
  printf("[READER-GOT-MUTEX-TO-ENTER-QUEUE]\n");
  // Come out of this loop when writers is 0.
  // TRAP for threads coz sometimes they come out the cond_wait()
  while (!(data.writers==0))
  {
    pthread_cond_wait(&data.readersQ, &data.lock);
  }
  printf("[READER-TO-START-READING]\n");
  data.readers++;
  pthread_mutex_unlock(&data.lock);

  /* read */
  printf("\nString: %s", data.buffer);

  pthread_mutex_lock (&data.lock);
  data.readers--;

  printf("[READER-DONE-READING]\n");
  // Doubt - Why do we signal only when readers are 0.
  if (data.readers==0)
  {
    pthread_cond_signal(&data.writersQ);
  }
  pthread_mutex_unlock(&data.lock);
  printf("[READER-EXIT]\n");

}

void writer (void)
{

}

void improved_writer (void)
{
  printf("[WRITER]\n");
  pthread_mutex_lock (&data.lock);
  printf("[WRITER-GOT-MUTEX-TO-ENTER-QUEUE]\n");
  data.writers++;
  while(!(data.readers==0) && (data.active_writers==0))
  {
    pthread_cond_wait(&data.writersQ, &data.lock);
  }
  data.active_writers++;
  printf("[WRITER-TO-START-WRITING]\n");

  pthread_mutex_unlock(&data.lock);

  /* write */
  printf("Enter a string:");
  scanf("%s", &data.buffer);

  printf("[WRITER-DONE-WRITING]\n");
  pthread_mutex_lock (&data.lock);
  data.writers--;
  data.active_writers--;

  // If anymore writer wants to write, give it preference over readers
  if(data.writers)
  {
    printf("[WRITER-SIGNAL-WRITER]\n");
    pthread_cond_signal(&data.writersQ);
  }
  else
  {
    printf("[WRITER-SIGNAL-READER]\n");
    pthread_cond_broadcast(&data.readersQ);
  }

  pthread_mutex_unlock(&data.lock);
  printf("[WRITER-EXIT]\n");

}


int main(void)
{
  int num_readers_tid = 2;
  int num_writers_tid = 2;
  assert(num_readers_tid<NUM_MAX_THREADS);
  assert(num_writers_tid<NUM_MAX_THREADS);

  pthread_t reader_tid[NUM_MAX_THREADS];
  pthread_t writer_tid[NUM_MAX_THREADS];

  pthread_mutex_init(&data.lock, NULL);
  pthread_cond_init(&data.readersQ, NULL);
  pthread_cond_init(&data.writersQ, NULL);

  printf("\n\n == READER WRITER PROBLEM - CONDITION VARIABLE == \n\n");
  for(int i=0; i<num_writers_tid; i++)
  {
    pthread_create(&writer_tid[i], NULL, &improved_writer, NULL);
    //pthread_create(&reader_tid[i], NULL, &writer, NULL);
  }
  for(int i=0; i<num_readers_tid; i++)
  {
    pthread_create(&reader_tid[i], NULL, &reader, NULL);
  }


  for(int i=0; i<num_readers_tid; i++)
  {
    pthread_join(reader_tid[i], NULL);
  }
  for(int i=0; i<num_writers_tid; i++)
  {
    pthread_join(reader_tid[i], NULL);
  }

  return 0;
}


