/*
Leetcode Easy 346 Moving Average From Data Stream

Output:
Next 1: 1.00
Next 10: 5.50
Next 3: 4.67
Next 5: 6.00
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *window;
    int size;
    int head;
    int count;
    double sum;
} MovingAverage;

// Function to create a moving average data structure with a given window size.
MovingAverage* movingAverageCreate(int size) {
    MovingAverage *obj = (MovingAverage*)malloc(sizeof(MovingAverage));
    obj->window = (int*)malloc(size * sizeof(int));
    obj->size = size;
    obj->head = 0;
    obj->count = 0;
    obj->sum = 0.0;
    return obj;
}

// Function to calculate the moving average from the data stream.
double movingAverageNext(MovingAverage* obj, int val) {
    // If the window is full, subtract the oldest value from the sum
    if (obj->count == obj->size) {
        obj->sum -= obj->window[obj->head];
    } else {
        obj->count++;
    }
    
    // Add the new value to the window and sum
    obj->window[obj->head] = val;
    obj->sum += val;
    
    // Move the head pointer to the next position
    obj->head = (obj->head + 1) % obj->size;
    
    // Calculate and return the average
    return obj->sum / obj->count;
}

// Function to free the memory allocated for the moving average data structure.
void movingAverageFree(MovingAverage* obj) {
    free(obj->window);
    free(obj);
}

int main() {
    MovingAverage* m = movingAverageCreate(3);
    printf("Next 1: %.2f\n", movingAverageNext(m, 1)); // Output: 1.00
    printf("Next 10: %.2f\n", movingAverageNext(m, 10)); // Output: 5.50
    printf("Next 3: %.2f\n", movingAverageNext(m, 3)); // Output: 4.67
    printf("Next 5: %.2f\n", movingAverageNext(m, 5)); // Output: 6.00
    movingAverageFree(m);
    return 0;
}

