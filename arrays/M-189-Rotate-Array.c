/* Rotate Arrays 

https://leetcode.com/problems/rotate-array/description/

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

