/*
Leetcode Medium 253. Meeting Rooms II

Given an array of meeting time intervals intervals where intervals[i] = [starti, endi], return the minimum number of conference rooms required.

Approach - 
1. Sort with start times
2. Use min heap for end times
3. Processing Intervals: Iterate through each interval and do the following:
   3.1 If the meeting with the smallest end time ends before the current meeting starts, remove it from the heap (free the room).
   3.2 Add the current meeting's end time to the heap.
   3.3 The size of the heap at any time will give the number of rooms needed.

Output:
Minimum number of conference rooms required: 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Definition for an interval
struct Interval {
    int start;
    int end;
};

// Comparator function for qsort to sort intervals by start time
int compareStart(const void* a, const void* b) {
    return ((struct Interval*)a)->start - ((struct Interval*)b)->start;
}

// Min-Heap structure
typedef struct {
    int* heapArray;
    int size;
    int capacity;
} MinHeap;

// Function to create a min-heap
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->heapArray = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    return minHeap;
}

// Function to swap two integers
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify the node at index i
void heapifyUp(MinHeap* minHeap, int i) {
    int parent = (i - 1) / 2;
    if (i && minHeap->heapArray[parent] > minHeap->heapArray[i]) {
        swap(&minHeap->heapArray[parent], &minHeap->heapArray[i]);
        heapifyUp(minHeap, parent);
    }
}

// Function to insert a key into the heap
void insertHeap(MinHeap* minHeap, int key) {
    if (minHeap->size == minHeap->capacity) {
        return;
    }
    minHeap->heapArray[minHeap->size] = key;
    minHeap->size++;
    heapifyUp(minHeap, minHeap->size - 1);
}

// Heapify the node at index i
void heapifyDown(MinHeap* minHeap, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int smallest = i;
    if (left < minHeap->size && minHeap->heapArray[left] < minHeap->heapArray[smallest]) {
        smallest = left;
    }
    if (right < minHeap->size && minHeap->heapArray[right] < minHeap->heapArray[smallest]) {
        smallest = right;
    }
    if (smallest != i) {
        swap(&minHeap->heapArray[smallest], &minHeap->heapArray[i]);
        heapifyDown(minHeap, smallest);
    }
}

// Function to remove and return the minimum element from the heap
int extractMin(MinHeap* minHeap) {
    if (minHeap->size <= 0) {
        return INT_MAX;
    }
    if (minHeap->size == 1) {
        minHeap->size--;
        return minHeap->heapArray[0];
    }
    int root = minHeap->heapArray[0];
    minHeap->heapArray[0] = minHeap->heapArray[minHeap->size - 1];
    minHeap->size--;
    heapifyDown(minHeap, 0);
    return root;
}

// Function to find the minimum number of conference rooms required
int minMeetingRooms(struct Interval* intervals, int intervalsSize) {
    if (intervalsSize == 0) {
        return 0;
    }

    // Sort the intervals by start time
    qsort(intervals, intervalsSize, sizeof(struct Interval), compareStart);

    // Create a min-heap to store end times of meetings
    MinHeap* minHeap = createMinHeap(intervalsSize);

    // Add the first meeting's end time to the heap
    insertHeap(minHeap, intervals[0].end);

    // Iterate through the remaining intervals
    for (int i = 1; i < intervalsSize; i++) {
        // If the meeting with the smallest end time is free, remove it from the heap
        if (minHeap->heapArray[0] <= intervals[i].start) {
            extractMin(minHeap);
        }
        // Add the current meeting's end time to the heap
        insertHeap(minHeap, intervals[i].end);
    }

    // The size of the heap is the number of conference rooms needed
    int result = minHeap->size;

    // Free the allocated memory
    free(minHeap->heapArray);
    free(minHeap);

    return result;
}

// Helper function to print the result (for testing)
void printResult(int result) {
    printf("Minimum number of conference rooms required: %d\n", result);
}

int main() {
    struct Interval intervals[] = {{0, 30}, {5, 10}, {15, 20}};
    int intervalsSize = sizeof(intervals) / sizeof(intervals[0]);

    int result = minMeetingRooms(intervals, intervalsSize);
    printResult(result);

    return 0;
}

