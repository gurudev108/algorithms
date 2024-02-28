/* From ChatGPT, verified on leetcode
215. Kth largest element in an array

a min-heap of size k is maintained to store the k largest elements encountered so far. 
As the program iterates through the array, it updates the min-heap if a larger element is found
*/

#include <stdio.h>
#include <stdlib.h>

// Function to swap two elements in the array.
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Min Heap functions
void minHeapifyDown(int arr[], int size, int index) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int smallest = index;

    if (leftChild < size && arr[leftChild] < arr[smallest]) {
        smallest = leftChild;
    }

    if (rightChild < size && arr[rightChild] < arr[smallest]) {
        smallest = rightChild;
    }

    if (smallest != index) {
        swap(&arr[index], &arr[smallest]);
        minHeapifyDown(arr, size, smallest);
    }
}

void buildMinHeap(int arr[], int size) {
    for (int i = size / 2 - 1; i >= 0; --i) {
        minHeapifyDown(arr, size, i);
    }
}

// Function to find the kth largest element using a min-heap.
int findKthLargest(int nums[], int numsSize, int k) {
    // Step 1 - Create a min-heap of size k to store the k largest elements.
    int* minHeap = (int*)malloc(k * sizeof(int));

    // Step 2 - Insert first k elements from the array into the min heap
    for (int i = 0; i < k; ++i) {
        minHeap[i] = nums[i];
    }

    // Step 3- Build the initial min-heap.
    buildMinHeap(minHeap, k);

    // Step 4 - Iterate through the remaining elements in the array - and replace if 
    for (int i = k; i < numsSize; ++i) {
        // If the current element is larger than the root of the min-heap, replace the root.
        if (nums[i] > minHeap[0]) {
            minHeap[0] = nums[i];
            minHeapifyDown(minHeap, k, 0);
        }
    }

    // The root of the min-heap now contains the kth largest element.
    int result = minHeap[0];
    free(minHeap);

    return result;
}

int main() {
    // Example usage:
    int nums[] = {3, 2, 1, 5, 4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int k = 2;

    int result = findKthLargest(nums, numsSize, k);

    printf("The %dth largest element is: %d\n", k, result);

    return 0;
}
