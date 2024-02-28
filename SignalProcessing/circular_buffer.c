#include <stdio.h>

#define BUFFER_SIZE 5

/*
   1  2  3  4  5  6
   head           tail
   Push new elements on tail after checking is_full, increment tail with %

   Pop new elements at head after checking is_full for empty, increment head with %
*/
struct circularBuffer
{
  int data[BUFFER_SIZE];
  int head;
  int tail;
  int is_full;
};

struct circularBuffer buffer;

int push(int num)
{
  if (buffer.is_full)
  {
    printf("\nBuffer full");
    return -1; 
  }

  buffer.data[buffer.tail] = num;

  buffer.tail = (buffer.tail+1)%BUFFER_SIZE;

  // ### IMP STEP to set full flag to true
  if (buffer.head == buffer.tail)
  {
    buffer.is_full = 1;
  }
  printf("\n Push %d head = %d tail = %d is_full = %d data@head = %d data@tail = %d",
    num, buffer.head, buffer.tail, buffer.is_full, buffer.data[buffer.head], buffer.data[buffer.tail]);
  return 0;
}

int pop()
{
  int data = 0;
  if ((buffer.head == buffer.tail) && (buffer.is_full == 0))
  {
    printf("\nBuffer empty");
    return -1;
  }

  data = buffer.data[buffer.head];
  buffer.head = (buffer.head + 1)%BUFFER_SIZE;

  // #IMP STEP to mark full flag to false
  buffer.is_full = 0;

  printf("\n Pop head = %d tail = %d is_full = %d data@head = %d data@tail = %d", 
    buffer.head, buffer.tail, buffer.is_full, buffer.data[buffer.head], buffer.data[buffer.tail]);
  return 0;
}

int main()
{

  pop();
  push(1);
  push(2);
  push(3);
  push(4);
  push(5);
  pop();
  push(6);
  push(7);
  push(8);
  pop();
  pop();
  pop();
  pop();
  pop();
  pop();

  return 0;
}
