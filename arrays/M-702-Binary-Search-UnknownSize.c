/*
https://leetcode.com/problems/search-in-a-sorted-array-of-unknown-size/description/

702. Search in a sorted array of unknown size
Difficult {Medium}
Topics {Array, BinarySearch}

You have a sorted array of unique elements and an unknown size. You do not have an access to the array but you can use the ArrayReader interface to access it. You can call ArrayReader.get(i) that:

returns the value at the ith index (0-indexed) of the secret array (i.e., secret[i]), or
returns 231 - 1 if the i is out of the boundary of the array.
You are also given an integer target.

Return the index k of the hidden array where secret[k] == target or return -1 otherwise.

You must write an algorithm with O(log n) runtime complexity.

 

Example 1:

Input: secret = [-1,0,3,5,9,12], target = 9
Output: 4
Explanation: 9 exists in secret and its index is 4.

Approach
Step 1 - Define search boundaries - start with left 0 right 1 and increment rightx2 to increase the search space
Step 2 - Binary Search
*/

/**
 * *********************************************************************
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * *********************************************************************
 *
 * int getElement(ArrayReader *, int index);
 */

int search(struct ArrayReader* reader, int target) {
    
    int left = 0;
    int right = 1;
    int mid = 0;
    if (getElement(reader, 0) == target) return 0;
    while (getElement(reader, right) < target)
    {
        left = right;
        right <<= 1;
    }
    //printf("left %d right %d", left, right);

    while (left <= right)
    {
      mid = left + ((right-left)>>1);
      printf("left %d mid %d right %d", left, mid, right);
      if (getElement(reader, mid) ==target)
      {
          return mid;
      }
      else if (getElement(reader, mid) < target)
      {
          left = mid +1;
      }
      else
      {
          right = mid -1;
      }
    }

    return -1;

}

