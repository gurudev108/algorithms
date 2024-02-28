/*
https://leetcode.com/problems/single-number-iii/
Topics {Array, Bitwise}

Given an integer array nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once. You can return the answer in any order.

You must write an algorithm that runs in linear runtime complexity and uses only constant extra space.

Example 1:

Input: nums = [1,2,1,3,2,5]
Output: [3,5]
Explanation:  [5, 3] is also a valid answer.

Approach
1. XOR every element - all elements occuring twice will be zero'ed
2. Now take any bit set and use it as a mask 
3. Use this mask to divide the numbers in the array into 2 groups
4. Both these groups will have numbers occuring twice and a number occuring once

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* singleNumber(int* nums, int numsSize, int* returnSize) {
    int xor = 0;
    int mask = 0;
    int* result = (int*)malloc(sizeof(int)*2);
    memset(result, 0, sizeof(int)*2);

    for (int i=0; i<numsSize; i++)
    {
        //xor has both elements that appear once
        xor ^= nums[i];
    }
    mask = xor & (-xor);
    for (int i=0; i<numsSize; i++)
    {
        if(nums[i] & mask)
        {
            result[0] ^= nums[i];
        }
        else
        {
            result[1] ^= nums[i];
        }
    }
    printf("%d %d", result[0], result[1]);
    return result;
    
}

int main()
{
  int nums[] = {1,2,1,3,2,5};
  int size = 0;
  int* result = singleNumber(nums, sizeof(nums)/sizeof(nums[0]), &size);
  for (int i=0; i<size; i++)
  {
    printf("%d ", result[i]);
  }
  return 0;
}
