/*
pthread_mutex_t lock
//Not used - Optional to initialize
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER

int pthread_mutex_init(pthread_mutex_t *lock, pthread_mutexattr_t * attrp)
pthread_mutex_init(&lock, NULL)

int pthread_mutex_destroy(pthread_mutex_t *lock)

// Not used
int pthread_mutexattr_init(pthread_mutexattr_t * attrp)
int pthread_mutexattr_destroy(pthread_mutexattr_t * attrp)

CAUTION while taking multiple locks 1 & 2 - Can cause deadlock
Fix - if(!pthread_mutex_trylock(&lock2)) - always returns without blocking. If the mutex2
is available it will lock the mutex and return 0. If mutex is not available, release lock 1 to prevent deadlock. 

*/

#include<pthread.h>
#include<stdio.h>
#include<string.h>

/* When we create threads, this is being updated by the function */
pthread_t tid[2];
pthread_mutex_t lock; 
  
void* trythis(void* arg) 
{ 
  int id = (int)(arg);
  
  printf("\n Thread %d has started\n", id);
  if (id ==0)
  {
    for (int j = 0; j < (0x0FFFFFFF); j++);
  }

    pthread_mutex_lock(&lock); 
  
    unsigned long i = 0; 
    printf("\n Job %d has started\n", id); 
  
    for (int i = 0; i < (0xFFFFFFFF); i++) 
        ; 
  
    printf("\n Job %d has finished\n", id); 
  
    pthread_mutex_unlock(&lock); 

    /* if we have to detach a thread where it doesnt need synchronisation
       then no need to call pthread_join, rather call detach

       pthread_detach(tid[i]);

       Since we are anyways returning we don't have to call exit.

       pthread_exit(NULL);
    */
    return NULL; 
} 

int main(void)
{
  int i = 0; 
  int error; 
  printf("\n\n == PTHREADS ==\n\n");
  if (pthread_mutex_init(&lock, NULL) != 0) 
  { 
    printf("\n mutex init has failed\n"); 
    return 1; 
  } 
  
  while (i < 2) 
  {
    error = pthread_create(&(tid[i]), 
                             NULL, 
                             &trythis, i); 
    if (error != 0)
    {
      printf("\nThread can't be created :[%s]", 
             strerror(error));
    }
    i++; 
  }

  pthread_join(tid[0], NULL); 
  pthread_join(tid[1], NULL); 
  pthread_mutex_destroy(&lock);

  return 0;

}

