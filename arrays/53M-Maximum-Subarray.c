#include <stdio.h>
#include <limits.h>

#define MAX(a,b) ((a>=b)?a:b)

int max_subarray_brute(int* nums, int numsSize)
{
  return 0;
}

int max_subarray_kadane(int* nums, int numsSize)
{
  int max_ending_here = 0;
  int max_so_far = 0;
  for (int i=0; i<numsSize; i++)
  {
    max_ending_here = MAX(nums[i], max_ending_here+nums[i]);
    max_so_far = MAX(max_ending_here, max_so_far);
  }
  return max_so_far;
}

int main()
{
    int arr[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    int n = sizeof(arr)/sizeof(arr[0]);
 
    int result = max_subarray_kadane(arr, n);
 
    printf("Max subarray = %d", result);
    return 0;
}
