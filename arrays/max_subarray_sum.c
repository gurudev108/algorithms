/* 
https://leetcode.com/problems/maximum-subarray/description/
Leetcode 53. Maximum Subarray
Difficulty {Medium}
Topics {Array, Divide&Conquer, DynamicProgramming}

Given an integer array nums, find the subarray with the largest sum, and return its sum.

Techie Delight - Maximum Sum Subarray Problem
https://www.techiedelight.com/maximum-subarray-problem-kadanes-algorithm/

Example 1:

Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: The subarray [4,-1,2,1] has the largest sum 6.
*/

#include <stdio.h>
#include <limits.h>

#define MAX(a,b) ((a>b)?a:b)

int max_subarray_brute(int* nums, int numsSize){
    int current_subarray = 0;
    int max_subarray = INT_MIN;
    for (int i=0; i<numsSize; i++)
    {
        current_subarray = 0;
        for(int j=i; j<numsSize; j++)
        {
            current_subarray += nums[j];
            max_subarray = MAX(max_subarray, current_subarray);
        }
    }
    return max_subarray;

}

/* Approach 2: Dynamic Programming, Kadane's Algorithm
*/
int max_subarray_kadane(int* nums, int numsSize){
	// stores the maximum sum subarray found so far
	int max_so_far = 0;
	// stores the max sum of subarray ending at current position
	int max_ending_here = 0;

	for (int i=0; i<numsSize; i++){
	  max_ending_here += nums[i];
	  max_ending_here = MAX(0, max_ending_here);

	  max_so_far = MAX(max_so_far, max_ending_here);
	}
	return max_so_far;
}

int main()
{
    int arr[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    int n = sizeof(arr)/sizeof(arr[0]);
 
    int result = max_subarray_kadane(arr, n);
 
    printf("Max subarray = %d", result);
    return 0;
}
