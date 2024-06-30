/*

88. Merge Sorted Array

Approach: 3 pointers

Output:
1st sorted array 1 2 3 0 0 0
2nd sorted array 2 5 6
Merged sorted array 1 2 2 3 5 6
*/

#include "stdio.h"

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n)
{
  int p1 = m-1;
  int p2 = n-1;

  for(int p=m+n-1; p>=0; p--)
  {
    if(p2<0)
    {
      break;
    }
    if(p1>=0 && (nums1[p1] > nums2[p2]))
    {
      nums1[p] = nums1[p1--];
    }
    else
    {
      nums1[p] = nums2[p2--];
    }
  }
}

void print(int* arr, int size)
{
  for (int i=0; i<size; i++)
  {
    printf(" %d", arr[i]);
  }
}
int main()
{
  int nums1[] = {1,2,3,0,0,0};
  int nums2[] = {2,5,6};
  int m = 3, n = 3;
  
  printf("\n1st sorted array");
  print(nums1, 6);
  printf("\n2nd sorted array");
  print(nums2, 3);
  merge(nums1, m+n, m, nums2, n, n);
  printf("\nMerged sorted array");
  print(nums1, 6);
  return 0;
}
