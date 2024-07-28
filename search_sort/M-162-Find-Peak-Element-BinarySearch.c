/*

Leetcode Medium 162 Find Peak Element

A peak element is an element that is strictly greater than its neighbors.

Given a 0-indexed integer array nums, find a peak element, and return its index. If the array contains multiple peaks, return the index to any of the peaks.

You may imagine that nums[-1] = nums[n] = -∞. In other words, an element is always considered to be strictly greater than a neighbor that is outside the array.

You must write an algorithm that runs in O(log n) time.

Input: nums = [1,2,1,3,5,6,4] 
Output: 5
Explanation: Your function can return either index number 1 where the peak element is 2, or index number 5 where the peak element is 6.

Approach:
Recursive or Iterative binary search
Binary search - this is not sorted, but since we need to find any peak, we can just go to the middle and try to find the peak associated with the slope at mid. 

Output:
Iterative result 5, Recursive result 5

*/

#include "stdio.h"

int search_iterative(int* nums, int numsSize)
{
  int left = 0, right = numsSize - 1, mid;

  while (left < right)
  {
    mid = (left + right)/2;
    if (nums[mid] > nums[mid+1])
    {
      right = mid;
    }
    else
    {
      left = mid+1;
    }
  }
  return left;
}

int helper(int* nums, int left, int right)
{
  int mid = left + (right - left)/2;
  if (left == right) return left;
  if (nums[mid] > nums[mid+1])
  {
    return helper(nums, left, mid);
  }
  else
  {
    return helper(nums, mid+1, right);
  }

}

int search_recursive(int* nums, int numsSize)
{
  int left = 0, right = numsSize -1;
  return helper(nums, left, right);
}

int main()
{
  int nums[] = {1,2,1,3,5,6,4};
  int numsSize = sizeof(nums)/sizeof(nums[0]);

  int result1 = search_iterative(nums, numsSize);
  int result2 = search_recursive(nums, numsSize);

  printf("Iterative result %d, Recursive result %d", result1, result2);
  return 0;
}

