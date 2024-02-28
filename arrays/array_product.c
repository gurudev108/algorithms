/*
https://leetcode.com/problems/product-of-array-except-self/description/

238. Product of Array Except Self
Difficulty {Medium}
Topics {Array, PrefixSum}

Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in O(n) time and without using the division operation.

Follow-up - Can you do that with O(1) space complexity
*/

#include <stdio.h>
#include <stdlib.h>
/**
 * Time Complexity O(n)
   Space Complexity O(n)
 */
/* Approach 1
Maintain an array left which will have product of all items on the left
right - which will have all the product of items on the right
*/
int* productExceptSelf(int* nums, int numsSize, int* returnSize){
    int * result = (int *)malloc(sizeof(int)*numsSize);
    int * left = (int *)malloc(sizeof(int)*numsSize);
    int * right = (int *)malloc(sizeof(int)*numsSize);

    left[0] = 1;
    right[numsSize-1] = 1;
    for(int i=1; i<numsSize; i++)
    {
        left[i] = left[i-1]* nums[i-1];
    }
    for(int i=numsSize-1; i>0; i--)
    {
        right[i-1] = right[i]* nums[i];
    }
    for(int i=0; i<numsSize; i++)
    {
        result[i] = left[i]* right[i];
    }
    *returnSize = numsSize;
    free(left);
    free(right);

    return result;

}

/**
 * Time Complexity O(n)
   Space Complexity O(n) optimized to O(1)
   Left array can be the result array
   Right array could just be a temp variable
 */
int* productExceptSelf_opt(int* nums, int numsSize, int* returnSize){
    int * result = (int *)malloc(sizeof(int)*numsSize);
    int temp = 1;

    result[0] = 1;
    for(int i=1; i<numsSize; i++)
    {
        result[i] = result[i-1]* nums[i-1];
    }
    for(int i=numsSize-1; i>=0; i--)
    {
        result[i] = result[i]* temp;
        temp = temp * nums[i];
    }
    *returnSize = numsSize;

    return result;

}

void print(int* nums, int size)
{
  printf("[");
  for (int i = 0; i<size; i++)
  {
    printf("%d,", nums[i]);
  }
  printf("]");
}

int main()
{
  int arr[] = {1,2,3,4};
  int numsSize = sizeof(arr)/sizeof(arr[0]);
  int returnSize = 0;

  print(arr, numsSize);
  int *result = productExceptSelf(arr, numsSize, &returnSize);
 
  print(result, returnSize);
  free(result);

  return 0;
 }
