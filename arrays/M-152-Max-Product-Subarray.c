/*
https://leetcode.com/problems/maximum-product-subarray/description/

152. Max Product Subarray

Given an integer array nums, find a subarray that has the largest product, and return the product.
The test cases are generated so that the answer will fit in a 32-bit integer.
*/

#include <stdio.h>

#define MAX(a,b) ((a>=b)?a:b)
#define MIN(a,b) ((a<=b)?a:b)

int maxProduct(int* nums, int numsSize)
{
	int current = nums[0];
	int max_so_far = nums[0];
	int min_so_far = nums[0];
	int result = max_so_far;
	for (int i=1; i<numsSize; i++)
	{
	  current = nums[i];
	  int temp_max = MAX(current, MAX(current*max_so_far, current*min_so_far));
	  min_so_far = MIN(current, MIN(current*min_so_far, current*max_so_far));
	  max_so_far = temp_max;
	  result = MAX(result, max_so_far); 
	}
	return result;
}

int main()
{
    int arr[] = { 2, 3, -2, 4 };
    int n = sizeof(arr)/sizeof(arr[0]);
 
    int result = maxProduct(arr, n);
 
    printf("Max Product subarray = %d", result);
    return 0;
}

