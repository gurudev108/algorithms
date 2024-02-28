/*
Leetcode Hard
315. Count of Smaller Numbers After Self
https://leetcode.com/problems/count-of-smaller-numbers-after-self/description/
Topics {Array, BinarySearch, Divide&Conquer, BinaryIndexedTree, SegmentTree, MergeSort, OrderedSet}
Difficult {Hard}

*/
#include <stdio.h>
#include <stdlib.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countSmaller_brute(int* nums, int numsSize, int* returnSize) {
    int count;
    int* counts = (int*) malloc (sizeof(int)*numsSize);
    
    for (int i=0; i<numsSize; i++)
    {
        counts[i] = 0;
        count = 0;
        for (int j=i+1; j<numsSize; j++)
        {
            if (nums[j]<nums[i])
            {
                count++;
            }
        }
        counts[i] = count;
	// For some reason on leetcode this is resulting in Segmentation fault
        //printf("%d ", counts[i]);
    }
    *returnSize = numsSize;
    return counts;
}

int main()
{
  int arr[] = {5,2,6,1};
  int size = 0;
  int *counts = countSmaller_brute(arr, sizeof(arr)/sizeof(arr[0]), &size);
  for(int i=0; i<size; i++)
  {
    printf("%d ", counts[i]);
  }
  return 0;
}
