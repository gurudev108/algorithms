/* 
Write Heapsort
*/

#include <stdio.h>

#define MAX(a,b) (a<b)?a:b
#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)
#define PARENT(i) (i-1/2)

void print_array(int *A, int len, char* str)
{
  printf("\n%s len:%d", str, len);
  for (int i=0; i<len; i++)
    printf(" %d", A[i]);
}x

void heapify(int* data, int size, int i)
{
  int smallest = i;
  if((LEFT(i) < size) && (data[LEFT(i)] < data[smallest]))
  {
    smallest = LEFT(i);
  }
  else if ((RIGHT(i) < size) && (data[RIGHT(i)] < data[smallest]))
  {
    smallest = RIGHT(i);
  }

  if(smallest != i)
  {
    int temp = data[i];
    data[i] = data[smallest];
    data[smallest] = temp;

    heapify(data, size, smallest);
  }
}

void buildHeap(int* data, int len)
{
  for(int i=PARENT(len-1); i>=0; i--)
  {
    heapify(data, len,  i);
  }
}

void heapsort(int *data, int len)
{
  /* Build a heap*/
  buildHeap(data, len);

  print_array(data, len, "After building min heap");

  for (int i=len-1; i>=0; i--)
  {
    int temp = data[0]; 
    data[0] = data[i];
    data[i] = temp;

    printf("\nSaving %d at index %d", temp, i);
    heapify(data, i, 0); 
  }


}

int main()
{
  int data[] = {5,7,8,4,9,3,2,0,1,6};
  int len = sizeof(data)/sizeof(data[0]);

  print_array(data, len, "Original array");

  heapsort(data, len);

  print_array(data, len, "After heapSort_minHeap");
  return 0;
}
