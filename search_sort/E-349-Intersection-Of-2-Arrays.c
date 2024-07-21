/*
Leetcode Easy 349 Intrsection of 2 arrays

Given two integer arrays nums1 and nums2, return an array of their 
intersection. Each element in the result must be unique and you may return the result in any order.

Approach:
1. Sort the arrays using qsort
2. Use 2 pointers like technique and have i,j, and index pointers

Output:
4, 9

Not verified on Leetcode - Timelimit exceeded @TODO
*/

#include "stdio.h"
#include "stdlib.h"


int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* resultSize);

int compare (const void *a, const void *b)
{
  return (*(int*)a - *(int*)b);
}

int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* resultSize)
{
  int index = 0, i=0, j=0;
  int *result = (int*) malloc(sizeof(int) * ((nums1Size < nums2Size)? nums1Size : nums2Size));
  qsort(nums1, nums1Size, sizeof(int), compare);
  qsort(nums2, nums2Size, sizeof(int), compare);

  while(i<nums1Size && j<nums2Size)
  {
    if(nums1[i] < nums2[j])
    {
      i++;
    }
    else if(nums2[j] < nums1[i])
    {
      j++;
    }
    else if(index == 0 || (result[index-1] != nums1[i]))
    // equal store it
    {
      result[index++] = nums1[i];
      i++; j++;
    }
  }
  *resultSize = index;
  return result;
}

int main()
{
  int nums1[] = {4,9,5};
  int nums2[] = {9,4,9,8,4};

  int nums1Size = sizeof(nums1)/sizeof(nums1[0]);
  int nums2Size = sizeof(nums2)/sizeof(nums2[0]);
  int resultSize;

  int *result = intersection(nums1, nums1Size, nums2, nums2Size, &resultSize);

  for (int i=0; i<resultSize; i++)
  {
    printf("%d ", result[i]);
  }

  free(result);
  return 0;
}
