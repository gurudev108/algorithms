/* Heap Sort 
Combines better attributes of Merge Sort (O(logn)) and Insertion sort (in place)
(Binary) Heap  data structure is an ARRAY viewed as a Complete Binary tree and has 2 properties 
1. Structural property - Similar to complete binary tree and last level Left Full
2. Heap property - Priority of a node depending on min or max heap will be less or more. By default min heap where getting minimum is O(1) where root node is the smallest. Useful in arranging in descending order by keeping A[0] at last index. 

For index starting at 0,
  Parent(i) return floor(i-1/2)
  Left(i) return 2i+2
  Right(i) return 2i+2
All of the above can be done through Bitwise operations

Interfaces 
- Heapify (A,i) O(logn)
    Assues binary tree rooted at Left(i) and Right(i) are heaps.
    1. Check largest (node, left child or right child)
    2. If largest is not node (i) 
       >> exchange A[i] <> A[largest] 
       >> Heapify (A, largest)
- Insert 
    1. Enlarge heap - Add the new node maintaining strucural propoerty - last level LEFT FULL
    2. Consider path from root to inserted node.
    3. Find topmost element on this path with higher priority than that of inserted node
    4. Insert at this location by shifting down the other elements on this path.
- Delete-min
    1. Replace top element with last element of heap
    2. Heapify(1)
- Build a heap O(n)
    Builds a heap using BOTTOM-UP approach from an unordered array in LINEAR TIME
    1. for (i=length[A]/2 to 1) Heapify(A,i)
- Heapsort
    1. Build-Heap(A)
    2. for (i= length[A] down to 2
         >>exchange A[1] <> A[i]
         >> heap-size[A]--
         >> Heapify(A,1)
*/

#include <stdio.h>

#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)
#define PARENT(i) (i-1/2)

void print_array(int *A, int len, char* str);

/* N = size of the heap */
void heapify_minHeap(int *A, int N, int i)
{
  int smallest = i;

  /* Find smallest among root (i) left and right child */
  if((LEFT(i) < N) && (A[LEFT(i)] < A[smallest]))
  {
    smallest = LEFT(i);
  }
  if((RIGHT(i) < N) && A[RIGHT(i)] < A[smallest])
  {
    smallest = RIGHT(i);
  }

  /* Swap and continue heapifying if root is not largest */
  if (smallest != i)
  {
    int temp = A[i];
    A[i] = A[smallest];
    A[smallest] = temp;

    /* Recursively heapify the affected sub-tree */
    heapify_minHeap(A, N, smallest);
  }
}

/* N = size of the heap */
void heapify_maxHeap(int *A, int N, int i)
{
  int largest = i;


  /* Find largest among root (i) left and right child */
  if((LEFT(i) < N) && (A[LEFT(i)] > A[largest]))
  {
    largest = LEFT(i);
  }
  if((RIGHT(i) < N) && A[RIGHT(i)] > A[largest])
  {
    largest = RIGHT(i);
  }

  /* Swap and continue heapifying if root is not largest */
  if (largest != i)
  {
    int temp = A[i];
    A[i] = A[largest];
    A[largest] = temp;

    /* Recursively heapify the affected sub-tree */
    heapify_maxHeap(A, N, largest);
  }
}

void buildMinHeap(int *A, int N, int len)
{
  for (int i=PARENT(len-1); i>=0; i--)
  {
    heapify_minHeap(A, N, i);
  }
}

void buildMaxHeap(int *A, int N, int len)
{
  for (int i=PARENT(len-1); i>=0; i--)
  {
    heapify_maxHeap(A, N, i);
  }
}


void insert_minHeap (int *A, int *len, int priority)
{
  A[*len] = priority;
  *len = *len + 1;
  heapify_minHeap(A, *len, *len);

}

void delete_min(int *A, int *size)
{
  /* Get the last element */
  int lastElement = A[*size-1];

  printf("\n last element:%d, A[0]:%d size:%d", lastElement, A[0], *size);

  /* Replace root with last element */
  A[0] = lastElement;

  *size = *size -1;

  heapify_minHeap(A, *size, 0);

}

void heapSort_minHeap(int *A, int len)
{
  int largest = 0;

  /* 1. Build a heap */
  buildMinHeap(A, len, len);
  print_array(A, len, "After building min heap");

  for (int i=len-1; i>=0; i--)
  {
    // Swap A[i] with A[0]
    int temp = A[0];
    A[0] = A[i];
    A[i] = temp;

    //printf("\nSwapping A[0]:%d with A[%d]:%d - Calling Heapify A(i,0)", A[0], i, A[i]);
    /* Heapify root element to get highest element at root again */
    heapify_minHeap(A, i, 0);
  }

}

void heapSort_maxHeap(int *A, int len)
{
  int largest = 0;

  /* 1. Build a heap */
  buildMaxHeap(A, len, len);

  print_array(A, len, "After building max heap");

  for (int i=len-1; i>=0; i--)
  {
    // Swap A[i] with A[0]
    int temp = A[0];
    A[0] = A[i];
    A[i] = temp;

    //printf("\nSwapping A[0]:%d with A[%d]:%d - Calling Heapify A(i,0)", A[0], i, A[i]);
    /* Heapify root element to get highest element at root again */
    heapify_maxHeap(A, i, 0);
  }

}

void print_array(int *A, int len, char* str)
{
  printf("\n%s len:%d", str, len);
  for (int i=0; i<len; i++)
    printf(" %d", A[i]);
}

int main()
{
  int in_arr[] = {5,7,8,4,9,3,2,0,1,6};
  int len = sizeof(in_arr)/sizeof(int);
  print_array(in_arr, len, "Original array");
  printf("\nRunning heapSort using min heap...\n");
  heapSort_minHeap(in_arr, len);
  print_array(in_arr, len, "After heapSort_minHeap");

  printf("\nResetting array");
  int in_arr1[] = {5,7,8,4,9,3,2,0,1,6};
  print_array(in_arr1, len, "Original array");
  printf("\nRunning heapSort using max heap...\n");
  heapSort_maxHeap(in_arr1, len);
  print_array(in_arr1, len, "After heapSort_maxHeap");
  

  buildMinHeap(in_arr1, len, len);
  print_array(in_arr1, len, "before delete_min");
  delete_min(in_arr1, &len);
  print_array(in_arr1, len, "after delete_min");
  
  insert_minHeap(in_arr1, &len, 100);
  print_array(in_arr1, len, "after inserting 100");

  return 0;
}
