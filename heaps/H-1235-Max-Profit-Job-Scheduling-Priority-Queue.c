/*
Priority Queue (Min-Heap) Approach
Approach:

Sort Jobs: Sort the jobs by their start times.
Min-Heap: Use a priority queue (min-heap) to store jobs, where the heap is ordered by job end times.
Track Profit: As we process each job, we remove all jobs from the heap that end before the current job starts and update the maximum profit.

Ouput: 300 INCORRECT 250 from DP approach
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a job
typedef struct Job {
    int startTime;
    int endTime;
    int profit;
} Job;

// Comparison function to sort jobs by startTime
int compareStartTime(const void *a, const void *b) {
    Job *jobA = (Job *)a;
    Job *jobB = (Job *)b;
    return jobA->startTime - jobB->startTime;
}

// Structure for min-heap node
typedef struct MinHeapNode {
    int endTime;
    int totalProfit;
} MinHeapNode;

// Min-Heap implementation
typedef struct MinHeap {
    MinHeapNode *array;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->capacity = capacity;
    minHeap->size = 0;
    minHeap->array = (MinHeapNode*)malloc(capacity * sizeof(MinHeapNode));
    return minHeap;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left].endTime < minHeap->array[smallest].endTime) {
        smallest = left;
    }

    if (right < minHeap->size && minHeap->array[right].endTime < minHeap->array[smallest].endTime) {
        smallest = right;
    }

    if (smallest != idx) {
        MinHeapNode temp = minHeap->array[idx];
        minHeap->array[idx] = minHeap->array[smallest];
        minHeap->array[smallest] = temp;
        minHeapify(minHeap, smallest);
    }
}

void insertMinHeap(MinHeap* minHeap, MinHeapNode node) {
    if (minHeap->size == minHeap->capacity) return;

    minHeap->size++;
    int i = minHeap->size - 1;
    minHeap->array[i] = node;

    while (i != 0 && minHeap->array[i].endTime < minHeap->array[(i - 1) / 2].endTime) {
        MinHeapNode temp = minHeap->array[i];
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        minHeap->array[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

MinHeapNode extractMin(MinHeap* minHeap) {
    if (minHeap->size == 0) {
        MinHeapNode empty = {0, 0};
        return empty;
    }

    MinHeapNode root = minHeap->array[0];
    if (minHeap->size > 1) {
        minHeap->array[0] = minHeap->array[minHeap->size - 1];
        minHeapify(minHeap, 0);
    }
    minHeap->size--;
    return root;
}

// Function to find the maximum profit using sorting and priority queue
int maxProfit(Job jobs[], int n) {
    // Sort jobs by start time
    qsort(jobs, n, sizeof(Job), compareStartTime);

    // Create a min-heap to store jobs
    MinHeap* minHeap = createMinHeap(n);

    int maxProfit = 0;
    int currentProfit = 0;

    for (int i = 0; i < n; i++) {
        // Remove jobs from heap that have ended before the current job's start time
        while (minHeap->size > 0 && minHeap->array[0].endTime <= jobs[i].startTime) {
            currentProfit -= minHeap->array[0].totalProfit;
            extractMin(minHeap);
        }

        // Add the current job to the heap
        MinHeapNode newNode = {jobs[i].endTime, jobs[i].profit};
        insertMinHeap(minHeap, newNode);
        currentProfit += jobs[i].profit;

        // Update maxProfit
        if (currentProfit > maxProfit) {
            maxProfit = currentProfit;
        }
    }

    free(minHeap->array);
    free(minHeap);
    return maxProfit;
}

int main() {
    // Example usage
    Job jobs[] = {{1, 2, 50}, {3, 5, 20}, {6, 19, 100}, {2, 100, 200}};
    int n = sizeof(jobs) / sizeof(jobs[0]);

    printf("Maximum Profit: %d\n", maxProfit(jobs, n));

    return 0;
}
