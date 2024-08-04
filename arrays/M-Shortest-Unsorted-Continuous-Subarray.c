/* 
Daily Coding Problem Book 1.2 - Locate smallest window to be sorted

Techie Delight
https://www.techiedelight.com/smallest-window-sorting-which-make-array-sorted/

Leetcode
Difficulty {Medium}
Topics {TwoPointers, Array, Stack, Greedy, Sorting, MonotonicStack}
 
581. Shortest Unsorted Continuous Subarray
https://leetcode.com/problems/shortest-unsorted-continuous-subarray/description/

Problem
Given an integer array, find the smallest window sorting which will make the entire array sorted in increasing order.
Input:  { 1, 2, 3, 7, 5, 6, 4, 8 }
Output: Sort the array from index 3 to 6

Input:  { 1, 3, 2, 7, 5, 6, 4, 8 }
Output: Sort the array from index 1 to 6

HINT/TIP
Use 2 pointers - left index and right index
Pass 1 to get the right index of the sub array - Keep track of running max from loop 0 to n-1 and take the last index that is less than running max coz the running max that is om the left will have to be moved all the way to right
Pass 2 to get the left index of the sub array - Keep track of running min this time and loop from n-1 to 0 and take the last index greater than running min coz the running min will have to be moved all the way to the left
*/

#include <stdio.h>
#include <limits.h>
// Function to find the smallest window in an array, sorting which will
// make the entire array sorted
void findSubarray(int arr[], int n)
{
	int running_max = INT_MIN;
	int running_min = INT_MAX;
	int left_index = -1;
	int right_index = -1;

	for (int i=0; i<n; i++)
	{
	  if (arr[i] > running_max) {
	    running_max = arr[i];
	  }
	  /* find the last position that is less than the maximum so far */
	  if (arr[i] < running_max) {
	    right_index = i;
	  }
	}
        for (int i=n-1; i>=0; i--)
        {
          if (arr[i] < running_min) {
            running_min = arr[i];
          }
	  /* find the last position that is more than the minimum so far */
          if (arr[i] > running_min) {
            left_index = i;
          }
        }
        printf("Sort the array from index %d to %d", left_index, right_index);
}

int main()
{
    int arr[] = { 1, 3, 2, 7, 5, 6, 4, 8 };
    int n = sizeof(arr)/sizeof(arr[0]);
 
    findSubarray(arr, n);
 
    return 0;
}

