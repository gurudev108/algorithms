#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int head;
  int tail;
  int capacity;
  int count;
  int *items;
} MyCircularQueue;

bool myCircularQueueIsFull(MyCircularQueue* obj);
bool myCircularQueueIsEmpty(MyCircularQueue* obj);

MyCircularQueue* myCircularQueueCreate(int k) {
  MyCircularQueue* queue = (MyCircularQueue* )malloc(sizeof(MyCircularQueue));
  queue->items = (int*)malloc(sizeof(int)*k);
  //memset(Queue.head, 0, sizeof(int)*k);
  queue->head = 0;
  queue->tail = -1;
  queue->count = 0;
  queue->capacity = k;
  printf("\nQueue created:%p items:%p sizeof(MyCircularQueue):%d sizeof(int)*k:%d", queue, queue->items, sizeof(MyCircularQueue), sizeof(int)*k);
  return queue;
}

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
  printf("\nEnQueue obj:%p value:%d count:%d head:%d tail:%d", obj, value, obj->count, obj->head, obj->tail);

  if(myCircularQueueIsFull(obj))
  {
    return false;
  }

  obj->tail++;
  if(obj->tail == obj->capacity)
  {
    obj->tail = 0;
  }
  obj->items[obj->tail] = value;

  obj->count++;

  printf("\nEnd of EnQueue obj:%p value:%d count:%d head:%d tail:%d", obj, value, obj->count, obj->head, obj->tail);

  return true;

  
}

bool myCircularQueueDeQueue(MyCircularQueue* obj) {
  printf("\nDeQueue obj:%p count:%d", obj, obj->count);
  if( myCircularQueueIsEmpty(obj) )
  {
    return false;
  }
  else
  {
    obj->head++;
    obj->count--;
    if(obj->head == obj->capacity)
    {
      obj->head = 0;
    }
    printf("\nEnd of DeQueue obj:%p count:%d head:%d tail:%d", obj, obj->count, obj->head, obj->tail);
    return true;
  }
}

int myCircularQueueFront(MyCircularQueue* obj) {
  printf("\nFront obj:%p count:%d", obj, obj->count);
  if( myCircularQueueIsEmpty(obj) )
  {
    return false;
  }
  else
  {
    return obj->items[obj->head];
  }
  
}

int myCircularQueueRear(MyCircularQueue* obj) {
  printf("\nRear obj:%p count:%d", obj, obj->count);
  if( myCircularQueueIsEmpty(obj) )
  {
    return false;
  }
  else
  {
    printf("\nmyEnd of Rear obj:%p count:%d returns:%d head:%d tail:%d", obj, obj->count, obj->items[obj->tail], obj->head, obj->tail);
    return obj->items[obj->tail];
  }  
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
  //printf("\nmyCircularQueueIsEmpty obj:%p count:%d", obj, obj->count);
  if (obj->count)
  {
    return false;
  }
  else
  {
    return true;
  }  
}

bool myCircularQueueIsFull(MyCircularQueue* obj) {
  //printf("\nmyCircularQueueIsFull obj:%p count:%d", obj, obj->count);
  if (obj->count == obj->capacity)
  {
    return true;
  }
  else
  {
    return false;
  }
  
}

void myCircularQueueFree(MyCircularQueue* obj) {
  printf("\nmyCircularQueueFree obj:%p count:%d", obj, obj->count);
  free(obj->items);
  free(obj);
}

int main()
/**
 * Your MyCircularQueue struct will be instantiated and called as such:
 */
  MyCircularQueue* obj = myCircularQueueCreate(3);
  bool param_1 = myCircularQueueEnQueue(obj, 1);
  param_1 = myCircularQueueEnQueue(obj, 2);
  param_1 = myCircularQueueEnQueue(obj, 3);
  param_1 = myCircularQueueEnQueue(obj, 4);
 
  bool param_2 = myCircularQueueDeQueue(obj);
 
  int param_3 = myCircularQueueFront(obj);
 
  int param_4 = myCircularQueueRear(obj);
 
  bool param_5 = myCircularQueueIsEmpty(obj);
 
  bool param_6 = myCircularQueueIsFull(obj);
 
  myCircularQueueFree(obj);

  return 0;
}
