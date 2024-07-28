/*

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define a structure for points
typedef struct {
    int x;
    int y;
    double distance;  // Distance from the origin
} Point;

// Function to calculate the distance from the origin
double calculateDistance(int x, int y) {
    return sqrt(x * x + y * y);
}

// Swap two points
void swap(Point* a, Point* b) {
    Point temp = *a;
    *a = *b;
    *b = temp;
}

// Max-heapify function
void maxHeapify(Point heap[], int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left].distance > heap[largest].distance) {
        largest = left;
    }

    if (right < size && heap[right].distance > heap[largest].distance) {
        largest = right;
    }

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        maxHeapify(heap, size, largest);
    }
}

// Insert a new point into the heap
void insert(Point heap[], int* size, Point point) {
    heap[(*size)++] = point;
    for (int i = (*size) / 2 - 1; i >= 0; i--) {
        maxHeapify(heap, *size, i);
    }
}

// Remove the root (maximum) element from the heap
void removeMax(Point heap[], int* size) {
    swap(&heap[0], &heap[--(*size)]);
    maxHeapify(heap, *size, 0);
}

// Function to find the k closest points to the origin
void kClosestPoints(Point points[], int n, int k) {
    Point* heap = (Point*)malloc(k * sizeof(Point));
    int size = 0;

    for (int i = 0; i < n; i++) {
        points[i].distance = calculateDistance(points[i].x, points[i].y);
        if (size < k) {
            insert(heap, &size, points[i]);
        } else if (points[i].distance < heap[0].distance) {
            removeMax(heap, &size);
            insert(heap, &size, points[i]);
        }
    }

    // Print the k closest points
    printf("The %d closest points to the origin are:\n", k);
    for (int i = 0; i < k; i++) {
        printf("(%d, %d)\n", heap[i].x, heap[i].y);
    }

    free(heap);
}

int main() {
    Point points[] = {
        {1, 3},
        {-2, 2},
        {5, 8},
        {0, 1}
    };
    int n = sizeof(points) / sizeof(points[0]);
    int k = 2;

    kClosestPoints(points, n, k);

    return 0;
}

