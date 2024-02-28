/* Leetcode 215. Kth largest element in the array

https://leetcode.com/problems/kth-largest-element-in-an-array/

Given an integer array nums and an integer k, return the kth largest element in the array.
Note that it is the kth largest element in the sorted order, not the kth distinct element.
Can you solve it without sorting?

Example 1:

Input: nums = [3,2,1,5,6,4], k = 2
Output: 5
Example 2:

Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
Output: 4

Constraints:

1 <= k <= nums.length <= 105
-104 <= nums[i] <= 104
*/

#include <stdio.h>

#define PARENT(i) ((i-1)/2)
#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)

void print_array (int *nums, int len, char* str)
{
  if(str)
  {
    printf("\n%s", str);
  }
  for (int i=0; i<len; i++)
  {
    printf(" %d", nums[i]);
  }
}

/* to keep track of k largest numbers we create min heap of size k
such that any time we can get the kth from the top by checking the min */
void heapify_minHeap(int *nums, int size, int i)
{
  int smallest = i;

  if ((LEFT(i) < size) && (nums[smallest] > nums[LEFT(i)]))
  {
    smallest = LEFT(i);
  }
  if ((RIGHT(i) < size) && (nums[smallest] > nums[RIGHT(i)]))
  {
    smallest = RIGHT(i);
  }
  if (smallest != i)
  {
    int temp = nums[i];
    nums[i] = nums[smallest];
    nums[smallest] = temp;

    heapify_minHeap(nums, size, smallest);
  }
}

int delete_min(int *nums, int* numsSize)
{
  int result = nums[0];

  nums[0] = nums[*numsSize - 1];
  *numsSize = *numsSize - 1;

  heapify_minHeap(nums, *numsSize, 0);

  return result;
}

int findKthLargest(int* nums, int numsSize, int k){

  /* Build a min heap of size numsSize */
  for (int i = PARENT(numsSize-1); i>=0; i--)
  {
    heapify_minHeap(nums, numsSize, i);
  }

  print_array(nums, numsSize, "Min Heap Built");

  while(numsSize > k)
  {
    delete_min(nums, &numsSize);
    print_array(nums, numsSize, "Delete_min done");
  }
  return nums[0];
}

int main()
{
  int A[] = {20,4,8,12,10,6};
  int len = sizeof(A)/sizeof(A[0]);
  int kth = findKthLargest(A, len, 4);
  printf("Expected 12 Actual %d", kth);
  return 0;
}

