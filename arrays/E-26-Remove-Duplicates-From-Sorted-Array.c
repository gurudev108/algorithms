/*
26. Remove Duplicates from Sorted Array
*/
#include <stdio.h>

// Function to remove duplicates from a sorted array
int removeDuplicates(int arr[], int n) {
    // Check if the array is empty or contains only one element
    if (n <= 1) {
        return n;
    }

    // Initialize the index to store unique elements
    int uniqueIndex = 0;

    // Iterate through the array to remove duplicates
    for (int i = 1; i < n; ++i) {
        // If the current element is different from the previous one, store it at the next unique index
        if (arr[i] != arr[uniqueIndex]) {
            uniqueIndex++;
            arr[uniqueIndex] = arr[i];
        }
    }

    // The length of the array without duplicates is (uniqueIndex + 1)
    return uniqueIndex + 1;
}

// Function to print an array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    // Example sorted array with duplicates: 1 2 2 3 4 4 4 5
    int arr[] = {1, 1, 2, 2, 3, 4, 4, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original Array:\n");
    printArray(arr, n);

    // Remove duplicates and get the new length of the array
    int newLength = removeDuplicates(arr, n);

    printf("\nArray after removing duplicates:\n");
    printArray(arr, newLength);

    return 0;
}

