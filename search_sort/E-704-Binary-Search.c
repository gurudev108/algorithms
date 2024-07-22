/*

Leetcode Easy 704. Binary Search

Given an array of integers nums which is sorted in ascending order, and an integer target, write a function to search target in nums. If target exists, then return its index. Otherwise, return -1.

You must write an algorithm with O(log n) runtime complexity

Example:
Input: nums = [-1,0,3,5,9,12], target = 9
Output: 4
Explanation: 9 exists in nums and its index is 4

Approach:
Use left, right, mid pointers and every time we compare mid with target we are reducing the search space to half. 

Output:
target 9 found at index 4

Verified on Leetcode 76-17
*/

#include "stdio.h"

int search(int* nums, int numsSize, int target)
{
  int left = 0, right = numsSize - 1, mid;

  while (left <= right)
  {
    mid = (left + right)/2;
    if (nums[mid] == target)
    {
      printf("target %d found at index %d", target, mid);
      return mid;
    }
    else if (nums[mid] < target)
    {
      left = mid + 1;
    }
    else
    {
      right = mid - 1;
    }
  }
  return -1;
}

int main()
{
  int nums[] = {-1,0,3,5,9,12};
  int target = 9;
  int numsSize = sizeof(nums)/sizeof(nums[0]);

  int result = search(nums, numsSize, target);

  return result;
}

