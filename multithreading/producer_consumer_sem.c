/* Produce Consumer with POSIX semaphores 

int sem_init(sem_t *semaphore, int pshared, int init);
int sem_destroy(sem_t *semaphore);
int sem_wait(sem_t *semaphore);      // P operation
int sem_trywait(sem_t *semaphore);  // conditional P operation
int sem_post(sem_t *semaphore);     // V operation

This semaphor is useful only for 1 producer and 1 consumer
For more than one use Condition Variable where you could signal to multiple threads.

USE 2 SEMAPHORES - empty and occupied
Use 2 locations - nextin, nextout
1 Buffer

*/

#include <semaphore.h>
/* for NULL */
#include <stddef.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h> // for sleep()


#define BUFF_SIZE 50
int buffer[BUFF_SIZE];
int nextin = 0;
int nextout = 0;
void* producer (void *);
void* consumer (void *);
sem_t empty, occupied;

int main(void)
{
  pthread_t tid1, tid2;
  int err = 0;
  int value = -1;

  printf("\n\n == SEMAPHORE ==\n\n");
  err = sem_init(&empty, 0, BUFF_SIZE);
  sem_getvalue(&empty, &value);
  printf("Semaphore empty returns:%d value:%d \n", err, value);
  err = sem_init(&occupied, 0, 0);
  sem_getvalue(&occupied, &value);
  printf("Semaphore occupied returns:%d value:%d\n", err, value);

  pthread_create(&tid1, NULL, &producer, NULL);
  pthread_create(&tid2, NULL, &consumer, NULL);

  //for (int k=0; k<0xFFFFFFFF; k++);
  //for (int k=0; k<0xFFFFFFFF; k++);
  printf("Waiting for producer thread to be over\n");
  pthread_join(tid1, NULL);
  printf("Waiting for consumer thread to be over\n");
  pthread_join(tid2, NULL);

  return 0;

}

void* producer (void *)
{
  int ch=0;
  int value = 0;

  while(1)
  {

    sem_getvalue(&empty, &value);
    //printf("[P]Producer WAITING semwait empty:%d\n", value);
    sem_wait(&empty);
    sem_getvalue(&empty, &value);
    printf("[P]INSIDE PRODUCER empty:%d Enter item to be produced\n", value);
    scanf("%d", &ch);
    buffer[nextin] = ch;
    if (++nextin >= BUFF_SIZE)
    {
      nextin = 0;
    }
    printf("[P]Produced item:%d\n", ch);
    sem_post(&occupied);
    sem_getvalue(&occupied, &value);
    printf("[P]Producer SIGNALED:%d occupied:%d\n", ch, value);
    sleep(1);
  }
}

void* consumer (void *)
{
  int  item=0;
  int value=0;

  while (1)
  {
    //for (int k=0; k<0xFFFFFFFF; k++);
    sem_getvalue(&occupied, &value);
    printf("[C]Consumer WAITING occupied:%d\n", value);
    sem_wait(&occupied);
    sem_getvalue(&occupied, &value);
    printf("[C]INSIDE CONSUMER:%d\n", value);
    item = buffer[nextout];
    if (++nextout >= BUFF_SIZE)
    {
      nextout = 0;
    }
    sleep(1);
    printf("[C]Consumed item:%d\n", item);
    sem_post(&empty);
    sem_getvalue(&empty, &value);
    printf("[C]Consumer SIGNALED empty:%d\n", value);
    //sleep(1);
  }

}
