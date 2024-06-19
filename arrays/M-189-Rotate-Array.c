/* Rotate Arrays - Approach 4 using reverse 

https://leetcode.com/problems/rotate-array/description/
Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.

Approach 2: Using Extra Array

Algorithm

We use an extra array in which we place every element of the array at its correct
position i.e. the number at index iii in the original array is placed at the
index (i+k)% length of array(i + k) \% \text{ length of array}(i+k)% length of array.
Then, we copy the new array to the original one.


Approach 4: Using Reverse
This approach is based on the fact that when we rotate the array k times, kk%nk elements from the back end of the array come to the front and the rest of the elements from the front shift backwards.

In this approach, we firstly reverse all the elements of the array. Then, reversing the first k elements followed by reversing the rest n−kn-kn−k elements gives us the required result.

Let n=7 and k=3.

Original List                   : 1 2 3 4 5 6 7
After reversing all numbers     : 7 6 5 4 3 2 1
After reversing first k numbers : 5 6 7 4 3 2 1
After revering last n-k numbers : 5 6 7 1 2 3 4 --> Result

*/


#include <stdio.h>

void reverse(int arr[], int start, int end) {
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void rotate(int arr[], int size, int k) {
    k = k % size; // to handle cases where k is larger than size

    // Reverse the entire array
    reverse(arr, 0, size - 1);

    // Reverse the first k elements
    reverse(arr, 0, k - 1);

    // Reverse the remaining elements
    reverse(arr, k, size - 1);
}

int main() {
    int nums[] = {1, 2, 3, 4, 5, 6, 7};
    int k = 3;
    int size = sizeof(nums) / sizeof(nums[0]);

    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    // Rotate the array
    rotate(nums, size, k);

    printf("Rotated array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    return 0;
}

