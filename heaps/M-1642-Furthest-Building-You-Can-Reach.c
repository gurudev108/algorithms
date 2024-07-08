/*
Leetcode 1642 Furthest building you could reach

Hint
1. Assume the problem is to check whether you can reach the last building or not.
2. You'll have to do a set of jumps, and choose for each one whether to do it using a ladder or bricks. It's always optimal to use ladders in the largest jumps.
3. Iterate on the buildings, maintaining the largest r jumps and the sum of the remaining ones so far, and stop whenever this sum exceeds b.

Output:
Furthest building index: 4

Verified on Leetcode with 86-59. 

The key here is to use the given bricks and ladders in the most optimal way to reach the furthest building.

1. ** Use a min-heap (priority queue)**: This helps to keep track of the largest jumps where we've used bricks. This way, if we run out of bricks, we can replace the largest brick usage with a ladder.

2. **Iterate through the buildings**: For each building, check the height difference to the next building.
    - If the next building is shorter or of the same height, continue.
    - If the next building is taller, you need to use either bricks or a ladder.

3. **Use bricks for smaller jumps**: Add the height difference to the min-heap.
    - If the size of the heap exceeds the number of ladders, use bricks for the smallest height difference (the root of the heap).
    - If you run out of bricks after using them, you can't proceed further and should return the current index.

4. **If you have ladders available**: Use them for the largest jumps by keeping track of jumps in the min-heap and replacing the smallest brick usage when necessary.

*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Include limits.h for INT_MAX

// A min-heap utility function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// A min-heap utility function to heapify a subtree rooted with node i
void heapify(int heap[], int n, int i) {
    int smallest = i; // Initialize smallest as root
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && heap[left] < heap[smallest])
        smallest = left;
    
    if (right < n && heap[right] < heap[smallest])
        smallest = right;
    
    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapify(heap, n, smallest);
    }
}

// Function to insert a new value into the min-heap
void insertHeap(int heap[], int *heapSize, int value) {
    heap[*heapSize] = value;
    int i = (*heapSize)++;
    
    // Fix the min-heap property if it is violated
    while (i != 0 && heap[(i - 1) / 2] > heap[i]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to extract the minimum value from the min-heap
int extractMin(int heap[], int *heapSize) {
    if (*heapSize <= 0)
        return INT_MAX;
    
    if (*heapSize == 1)
        return heap[--(*heapSize)];
    
    int root = heap[0];
    heap[0] = heap[--(*heapSize)];
    heapify(heap, *heapSize, 0);
    
    return root;
}

int furthestBuilding(int* heights, int heightsSize, int bricks, int ladders) {
    int *heap = (int*)malloc(heightsSize * sizeof(int));
    int heapSize = 0;
    int totalBricksUsed = 0;
    
    for (int i = 0; i < heightsSize - 1; ++i) {
        int diff = heights[i + 1] - heights[i];
        
        if (diff > 0) {
            insertHeap(heap, &heapSize, diff);
            
            if (heapSize > ladders) {
                totalBricksUsed += extractMin(heap, &heapSize);
            }
            
            if (totalBricksUsed > bricks) {
                free(heap);
                return i;
            }
        }
    }
    
    free(heap);
    return heightsSize - 1;
}

// Example usage
int main() {
    int heights[] = {4, 2, 7, 6, 9, 14, 12};
    int heightsSize = sizeof(heights) / sizeof(heights[0]);
    int bricks = 5;
    int ladders = 1;
    
    int result = furthestBuilding(heights, heightsSize, bricks, ladders);
    printf("Furthest building index: %d\n", result);
    
    return 0;
}

/*
Explanation:
- We maintain a min-heap to track the largest jumps where bricks were used.
- For each jump, we use bricks initially and store the height difference in the heap.
- When the heap size exceeds the number of ladders, it indicates that we have more height differences than ladders available. We then use bricks for the smallest height difference (extracted from the heap).
- If the total bricks used exceed the available bricks, we return the current index, as we cannot proceed further.

This approach ensures that we use the ladders for the largest jumps and bricks for smaller jumps, optimizing the usage of both resources.
*/
