/*
Good morning! Here's your coding interview problem for today.

This problem was asked by WhatsApp.

Given an array of integers out of order, determine the bounds of the smallest window that must be sorted in order for the entire array to be sorted. For example, given [3, 7, 5, 6, 9], you should return (1, 3).

Assuming, sorted as increasing order sorted
*/

#include <stdio.h>
#include <limits.h>

void smallest_window(int* nums, int size, int* start, int* end)
{
  int left = 0;
  int right = size - 1;
  int min = INT_MAX;
  int max = INT_MIN;

  // 1. Find the left boundary
  while(nums[left] < nums[left+1])
  {
    left++;
  }

  // 2. Find the right boundary
  while (nums[right] > nums[right-1])
  {
    right--;
  }

  // 3. Find the min and max in the array (left, right)
  for (int i=left; i<right; i++)
  {
    if(min>nums[i])
    {
      min = nums[i];
    }
    if (max<nums[i])
    {
      max = nums[i];
    }
  }

  //4. Check if fine tuning is needed by comparing min and max to outside of left, right
  while(left>0 && nums[left-1]>min)
  {
    left--;
  }
  while(right<size-1 && nums[right+1]<max)
  {
    right++;
  }

  *start = left;
  *end = right;
}

int main()
{
  int nums[] = {3,7,5,6,9};
  int left, right = -1;
  int size = sizeof(nums)/sizeof(nums[0]);
  smallest_window(nums, size, &left, &right);
  printf("\n(%d, %d", left, right);
  return 0;
}
