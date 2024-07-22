/*

Leetcode 33 Search in rotated sorted array

Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.
You must write an algorithm with O(log n) runtime complexity

Example:
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Approach:
1. Use basic binary search structure (left, right, mid, while loop)
2. Check which half is sorted
3. Now compare target with mid and left/right, to adjust left, right as mid+1 or mid-1

Output:
target 0 found at index 4

Verified on Leetcode 100-5
*/

#include <stdio.h>

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
    else if (nums[mid] >= nums[left] )
    {
      // left half is sorted
      if ((target < nums[mid]) && (target >= nums[left]))
      {
        right = mid - 1;
      }
      else
      {
        left = mid + 1;
      }
    }
    else
    {
      // right half is sorted
      if ((target > nums[mid]) && (target <= nums[right]))
      {
        left = mid + 1;
      }
      else
      {
        right = mid - 1;
      }
    }
  }
  return -1;
}

int main()
{
  int nums[] = {4,5,6,7,0,1,2};
  int target = 0;
  int numsSize = sizeof(nums)/sizeof(nums[0]);

  int result = search(nums, numsSize, target);

  return result;
}

