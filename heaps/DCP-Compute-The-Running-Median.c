/*

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
void minHeapifyUp(int arr[], int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (arr[index] < arr[parentIndex]) {
            swap(&arr[index], &arr[parentIndex]);
            index = parentIndex;
        } else {
            break;
        }
    }
}

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

void insertMinHeap(int arr[], int* size, int element) {
    (*size)++;
    arr[*size - 1] = element;
    minHeapifyUp(arr, *size - 1);
}

int extractMin(int arr[], int* size) {
    if (*size == 0) {
        fprintf(stderr, "Error: Min heap is empty.\n");
        exit(EXIT_FAILURE);
    }

    int minElement = arr[0];
    arr[0] = arr[*size - 1];
    (*size)--;
    minHeapifyDown(arr, *size, 0);

    return minElement;
}

// Max Heap functions
void maxHeapifyUp(int arr[], int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (arr[index] > arr[parentIndex]) {
            swap(&arr[index], &arr[parentIndex]);
            index = parentIndex;
        } else {
            break;
        }
    }
}

void maxHeapifyDown(int arr[], int size, int index) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int largest = index;

    if (leftChild < size && arr[leftChild] > arr[largest]) {
        largest = leftChild;
    }

    if (rightChild < size && arr[rightChild] > arr[largest]) {
        largest = rightChild;
    }

    if (largest != index) {
        swap(&arr[index], &arr[largest]);
        maxHeapifyDown(arr, size, largest);
    }
}

void insertMaxHeap(int arr[], int* size, int element) {
    (*size)++;
    arr[*size - 1] = element;
    maxHeapifyUp(arr, *size - 1);
}

int extractMax(int arr[], int* size) {
    if (*size == 0) {
        fprintf(stderr, "Error: Max heap is empty.\n");
        exit(EXIT_FAILURE);
    }

    int maxElement = arr[0];
    arr[0] = arr[*size - 1];
    (*size)--;
    maxHeapifyDown(arr, *size, 0);

    return maxElement;
}

// Function to compute the running median.
void runningMedian(int numbers[], int n) {
    // Step 1 - Create a max heap and a min heap
    int* maxHeap = (int*)malloc(n * sizeof(int));
    int maxHeapSize = 0;

    int* minHeap = (int*)malloc(n * sizeof(int));
    int minHeapSize = 0;

    // Step 2 - Start inserting numbers from the array into max heap or min heap 
    // based on comparison between numbers[i] and maxHeap[0]. First element goes into maxheap

    for (int i = 0; i < n; ++i) {
        if (maxHeapSize == 0 || numbers[i] < maxHeap[0]) {
            insertMaxHeap(maxHeap, &maxHeapSize, numbers[i]);
        } else {
            insertMinHeap(minHeap, &minHeapSize, numbers[i]);
        }

        // Step 3 - Balance the heaps
        if (maxHeapSize > minHeapSize + 1) {
            int root = extractMax(maxHeap, &maxHeapSize);
            insertMinHeap(minHeap, &minHeapSize, root);
        } else if (minHeapSize > maxHeapSize) {
            int root = extractMin(minHeap, &minHeapSize);
            insertMaxHeap(maxHeap, &maxHeapSize, root);
        }

        // Step 4 - Calculate and print the median
        if (maxHeapSize == minHeapSize) {
            double median = (maxHeap[0] + minHeap[0]) / 2.0;
            printf("Median after %d elements: %.2f\n", i + 1, median);
        } else {
            printf("Median after %d elements: %d\n", i + 1, maxHeap[0]);
        }
    }

    free(maxHeap);
    free(minHeap);
}

int main() {
    // Example usage:
    int numbers[] = {12, 4, 5, 3, 8, 7};
    int n = sizeof(numbers) / sizeof(numbers[0]);

    runningMedian(numbers, n);

    return 0;
}

