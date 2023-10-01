/*
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.
Clarifications?
1. Negative numbers?
2. Numbers are sorted? or can we sort?

*/

#include <stdio.h>
#include <stdlib.h>


// Input array already sorted - Use 2 pointers in one pass
int* threeSum(int* nums, int numsSize, int target, int* returnSize)
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
