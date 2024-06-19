#include <stdio.h>

void minHeapify(int* nums, int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && nums[left] < nums[smallest])
        smallest = left;

    if (right < size && nums[right] < nums[smallest])
        smallest = right;

    if (smallest != i) {
        // Swap nums[i] and nums[smallest]
        int temp = nums[i];
        nums[i] = nums[smallest];
        nums[smallest] = temp;

        // Recursively heapify the affected sub-tree
        minHeapify(nums, size, smallest);
    }
}

void buildMinHeap(int* nums, int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        minHeapify(nums, size, i);
}

int findKthLargest(int* nums, int numsSize, int k) {
    // Build a min-heap from the first k elements of the array
    buildMinHeap(nums, k);

    // Process the remaining elements of the array
    for (int i = k; i < numsSize; i++) {
        // If the current element is greater than the root of the min-heap,
        // replace the root with the current element and heapify again
        if (nums[i] > nums[0]) {
            int temp = nums[0];
            nums[0] = nums[i];
            nums[i] = temp;
            minHeapify(nums, k, 0);
        }
    }

    // The kth largest element is at the root of the min-heap
    return nums[0];
}

int main() {
    int nums[] = {3, 2, 1, 5, 6, 4};
    int k = 2;
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    printf("The %dth largest element is: %d\n", k, findKthLargest(nums, numsSize, k));

    return 0;
}

