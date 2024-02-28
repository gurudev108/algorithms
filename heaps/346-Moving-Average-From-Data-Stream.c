/* Easy

Given a stream of integers and a window size, calculate the moving average of all integers in the sliding window.

Implement the MovingAverage class:

MovingAverage(int size) Initializes the object with the size of the window size.
double next(int val) Returns the moving average of the last size values of the stream.

Example 1:

Input
["MovingAverage", "next", "next", "next", "next"]
[[3], [1], [10], [3], [5]]
Output
[null, 1.0, 5.5, 4.66667, 6.0]

Explanation
MovingAverage movingAverage = new MovingAverage(3);
movingAverage.next(1); // return 1.0 = 1 / 1
movingAverage.next(10); // return 5.5 = (1 + 10) / 2
movingAverage.next(3); // return 4.66667 = (1 + 10 + 3) / 3
movingAverage.next(5); // return 6.0 = (10 + 3 + 5) / 3

*/

#include <stdio.h> 

typedef struct {
  int* queue;
  int size;
  int head; // new items get added here, its like the end of the line
  int tail; // items get popped from here, its like the front of the line
  int is_full;
  int ma;
} MovingAverage;


MovingAverage* movingAverageCreate(int size) {
  MovingAverage* obj = (struct MovingAverage*)malloc(sizeof(struct MovingAverage));
  obj->queue = (int *)malloc(sizeof(int)*size);
  obj->window = size;
  obj->head = 0;
  obj->tail = 0;
  return obj;
}


double movingAverageNext(MovingAverage* obj, int val) {
  // If queue is full, 
  if(obj->is_full && (obj->head == obj->tail))
  {
    return -1;
  }
  else
  {
    /* Queue not full yet */
    int count = (obj->head + obj->size - obj->tail)%obj->size;
    obj->head = (obj->head+1)%obj->size;
    obj->queue[head] = val;
    if (obj->head == obj->tail)
    {
      obj->is_full = 1;
    }
    obj->ma = (obj->ma*count + val)/(count+1);
  }
}

void movingAverageFree(MovingAverage* obj) {
    
}

int main()
{
  MovingAverage* obj = movingAverageCreate(size);
  double param_1 = movingAverageNext(obj, val);
 
  movingAverageFree(obj);
  return 0;
}
