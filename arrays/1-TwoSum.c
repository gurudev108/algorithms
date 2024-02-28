/*
1. Two Sum
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

Clarifications?
1. Negative numbers?
2. Numbers are sorted? or can we sort?

*/

#include <stdio.h>
#include <stdlib.h>

// Brute Force O(n2)
int* twoSum1(int* nums, int numsSize, int target, int* returnSize)
{
  int *result = (int *)malloc(sizeof(int)*2);
  for (int i = 0; i<numsSize; i++)
  {
    for (int j=i+1; j<numsSize; j++)
    {
      if (target == nums[i] + nums[j])
      {
        result[0] = i;
        result[1] = j;
        *returnSize = 2;
        return result; 
      }
    }
  }
  return NULL;
}

// Input array already sorted - Use 2 pointers in one pass
int* twoSum2(int* nums, int numsSize, int target, int* returnSize)
{
  int left = 0;
  int right = numsSize - 1;
  int sum = 0;
  int *result = (int *)malloc(sizeof(int)*2);

  while (left<right)
  {
    sum = nums[left] + nums[right];
    if (sum == target)
    {
      result[0] = left;
      result[1] = right;
      *returnSize = 2;
      return result;
    }
    else if (sum < target)
    {
      left++;
    }
    else
    {
      right--;
    }
  }
  result[0] = -1;
  result[1] = -1;
  *returnSize = 2;
  return result;
}

int main()
{
  int nums[] = {2,7,11,15};
  int target = 9;
  int resultSize = 0;
  int *result = twoSum2(nums, sizeof(nums)/sizeof(nums[0]), target, &resultSize);
  for (int i=0; i<resultSize; i++)
  {
    printf(" %d", result[i]);
  }
  return 0;
}
