/*
Leetcode 857 Minium cost to hire k workers

To solve the problem of hiring exactly `k` workers with the minimum cost while satisfying the given conditions, we need to focus on the wage-to-quality ratio for each worker. The goal is to select a group of `k` workers such that the sum of their wages is minimized while maintaining the proportional pay condition.

Approach

1. **Calculate Wage-to-Quality Ratio**: For each worker, compute the ratio of their wage to their quality. This ratio represents how much money is required per unit of quality for that worker.
2. **Sort by Ratio**: Sort all workers based on their wage-to-quality ratio in ascending order. This way, we prioritize workers who provide more quality per unit of wage.
3. **Use a Max-Heap**: Use a max-heap to keep track of the `k` workers with the highest quality. This allows us to maintain the total quality of the current group and ensure we can quickly adjust the group to minimize the cost.
4. **Iterate and Compute Minimum Cost**: Iterate through the sorted workers, maintaining the sum of the qualities of the current `k` workers. For each worker, calculate the potential total cost to hire the current group and update the minimum cost accordingly.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

// Structure to store worker's data
typedef struct {
    double ratio;
    int quality;
} Worker;

// Comparator function for qsort
int compare(const void *a, const void *b) {
    double diff = ((Worker *)a)->ratio - ((Worker *)b)->ratio;
    return (diff > 0) - (diff < 0);
}

// Function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify a subtree rooted with node i
void heapify(int heap[], int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left] > heap[largest])
        largest = left;

    if (right < n && heap[right] > heap[largest])
        largest = right;

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        heapify(heap, n, largest);
    }
}

// Function to insert a new value into the max-heap
void insertHeap(int heap[], int *heapSize, int value) {
    heap[*heapSize] = value;
    int i = (*heapSize)++;

    while (i != 0 && heap[(i - 1) / 2] < heap[i]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to extract the maximum value from the max-heap
int extractMax(int heap[], int *heapSize) {
    if (*heapSize <= 0)
        return INT_MIN;

    if (*heapSize == 1)
        return heap[--(*heapSize)];

    int root = heap[0];
    heap[0] = heap[--(*heapSize)];
    heapify(heap, *heapSize, 0);

    return root;
}

// Function to calculate the minimum cost to hire k workers
double mincostToHireWorkers(int* quality, int qualitySize, int* wage, int wageSize, int k) {
    Worker workers[qualitySize];
    for (int i = 0; i < qualitySize; ++i) {
        workers[i].ratio = (double)wage[i] / quality[i];
        workers[i].quality = quality[i];
    }

    qsort(workers, qualitySize, sizeof(Worker), compare);

    int maxHeap[k];
    int heapSize = 0;
    int totalQuality = 0;
    double minCost = DBL_MAX;

    for (int i = 0; i < qualitySize; ++i) {
        totalQuality += workers[i].quality;
        insertHeap(maxHeap, &heapSize, workers[i].quality);

        if (heapSize > k) {
            totalQuality -= extractMax(maxHeap, &heapSize);
        }

        if (heapSize == k) {
            double cost = totalQuality * workers[i].ratio;
            if (cost < minCost) {
                minCost = cost;
            }
        }
    }

    return minCost;
}

// Example usage
int main() {
    int quality[] = {3, 1, 10, 10, 1};
    int wage[] = {4, 8, 2, 2, 7};
    int k = 3;

    double result = mincostToHireWorkers(quality, 3, wage, 3, k);
    printf("Minimum cost to hire %d workers: %.5f\n", k, result);

    return 0;
}

/*
Explanation:

1. **Worker Structure**: A `Worker` structure is used to store the ratio and quality of each worker.
2. **Sorting**: Workers are sorted based on their wage-to-quality ratio using `qsort`.
3. **Heap Operations**: Max-heap operations are performed to keep track of the `k` workers with the highest quality. This is essential to ensure the total quality sum is minimized.
4. **Iterating Through Workers**: The code iterates through the sorted workers and keeps updating the minimum cost required to hire `k` workers.

This solution ensures that the total cost is minimized while satisfying the conditions given in the problem.
*/
