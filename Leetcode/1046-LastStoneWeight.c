/*
You are given an array of integers stones where stones[i] is the weight of the ith stone.

We are playing a game with the stones. On each turn, we choose the heaviest two stones and smash them together. Suppose the heaviest two stones have weights x and y with x <= y. The result of this smash is:

If x == y, both stones are destroyed, and
If x != y, the stone of weight x is destroyed, and the stone of weight y has new weight y - x.
At the end of the game, there is at most one stone left.

Return the weight of the last remaining stone. If there are no stones left, return 0.
*/

#include <stdio.h>

#define PARENT(i) (((i)-1)/2)
#define LEFT(i) ((2*(i)+1))
#define RIGHT(i) ((2*(i)+2))

void heapify(int *stones, int size, int i)
{
  int largest = i;

  if((LEFT(i) < size) && stones[largest] < stones[LEFT(i)])
  {
    largest = LEFT(i);
  }
  if((RIGHT(i) < size) && stones[largest] < stones[RIGHT(i)])
  {
    largest = RIGHT(i);
  }
  if (largest!=i)
  {
    int temp = stones[largest];
    stones[largest] = stones[i];
    stones[i] = temp;

    heapify(stones, size, largest);
  }

}

int pop_max(int * stones, int *size)
{
  int result = stones[0];
  stones[0] = stones[*size-1];
  *size = *size - 1;
  heapify(stones, *size, 0);
  return result;
}

void push(int * stones, int *size, int num)
{
  int index = *size;
  stones[index] = num;
  while (stones[PARENT(index)] < stones[index]) 
  {
    int temp = stones[index];
    stones[index] = stones[PARENT(index)];
    stones[PARENT(index)] = temp;
    index = PARENT(index);
  }
  *size = *size + 1;
}

void print_array(int* stones, int stonesSize)
{
  printf("\nSize=%d Array = ", stonesSize);
  for (int i=0; i<stonesSize; i++)
  {
    printf(" %d", stones[i]);
  }
}

int lastStoneWeight(int* stones, int stonesSize){

  /* Build a max heap */
  for (int i=PARENT(stones[stonesSize-1]); i>=0; i--)
  {
    heapify(stones, stonesSize, i);
  }

  while(stonesSize >1)
  {
    print_array(stones, stonesSize);
    /* Remove max stone and then remove another max stone */
    int stone1 = pop_max(stones, &stonesSize);
    int stone2 = pop_max(stones, &stonesSize);
    printf("\nstone1 %d stone2 %d", stone1, stone2);
    if (stone1 != stone2)
    {
      int stone3 = (stone1>stone2)? stone1-stone2: stone2-stone1;
      printf(" stone3 %d stoneSize %d", stone3, stonesSize);
      /* Add the resulting stone into heap */
      push(stones, &stonesSize, stone3);
    }

  }
  if (stonesSize == 1)
  {
    return stones[0];
  }
  else
  {
    return 0;
  }
}
int main()
{
  int stones[] = {2,7,4,1,8,1};
  int len = sizeof(stones)/sizeof(stones[0]);
  int result = lastStoneWeight( stones, len);
  printf("lastStoneWeight =%d", result);
  return 0;
} 

