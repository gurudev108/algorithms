#include<stdio.h>

void merge(int* nums, int start, int mid, int end)
{
  // array mid..end
  int n1 = mid - start + 1;
  // array mid + 1..end
  int n2 = end - mid;

  int num1[n1];
  int num2[n2];

:wq:
}

void mergeSort(int* nums, int start, int end)
{
  // ****IMP - MISSED IT *****
  if(start<end)
  {
    int mid = start + (end - start)/2;
    mergeSort(nums, start, mid);
    mergeSort(nums, mid+1, end);
    merge(nums, start, mid, end);
  }
}


int main()
{
  int nums[] = {9,7,5,3,1,0,2,4,6,8};
  int size = sizeof(nums)/sizeof(nums[0]);
  print(nums, size);
  mergeSort(nums, 0, size-1);
  print(nums, size);
  return 0;
}
