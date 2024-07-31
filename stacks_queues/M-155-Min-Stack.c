/*
Leetcode 155 Min Stack

Approach:
To implement a MinStack that supports push, pop, top, and getMin operations in constant time (O(1)), use 2 stacks 

push, pop in O(1) is easy

Output:
Minimum: -3
Top: 0
Minimum: -2
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int* data;
    int* minData;
    int top;
    int capacity;
} MinStack;

/** Initialize your data structure here. */
MinStack* minStackCreate(int capacity) {
    MinStack* stack = (MinStack*)malloc(sizeof(MinStack));
    stack->data = (int*)malloc(capacity * sizeof(int));
    stack->minData = (int*)malloc(capacity * sizeof(int));
    /* @TODO-IMP - init value of top = -1 */
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

/** Push element val onto stack. */
void minStackPush(MinStack* obj, int val) {
    if (obj->top == obj->capacity - 1) {
        // Reallocate memory if stack capacity is full
        obj->capacity *= 2;
        /* @TODO-IMP - use realloc to double capacity when full */
        obj->data = (int*)realloc(obj->data, obj->capacity * sizeof(int));
        obj->minData = (int*)realloc(obj->minData, obj->capacity * sizeof(int));
    }
    obj->data[++(obj->top)] = val;
    if (obj->top == 0) {
        obj->minData[obj->top] = val;
    } else {
        obj->minData[obj->top] = (val < obj->minData[obj->top - 1]) ? val : obj->minData[obj->top - 1];
    }
}

/** Removes the element on the top of the stack. */
void minStackPop(MinStack* obj) {
    if (obj->top >= 0) {
        obj->top--;
    }
}

/** Get the top element. */
int minStackTop(MinStack* obj) {
    if (obj->top >= 0) {
        return obj->data[obj->top];
    }
    return INT_MIN; // Stack is empty
}

/** Retrieve the minimum element in the stack. */
int minStackGetMin(MinStack* obj) {
    if (obj->top >= 0) {
        return obj->minData[obj->top];
    }
    return INT_MIN; // Stack is empty
}

/** Free the stack */
void minStackFree(MinStack* obj) {
    free(obj->data);
    free(obj->minData);
    free(obj);
}

// Example usage
int main() {
    MinStack* minStack = minStackCreate(10);
    minStackPush(minStack, -2);
    minStackPush(minStack, 0);
    minStackPush(minStack, -3);
    printf("Minimum: %d\n", minStackGetMin(minStack)); // Returns -3
    minStackPop(minStack);
    printf("Top: %d\n", minStackTop(minStack));       // Returns 0
    printf("Minimum: %d\n", minStackGetMin(minStack)); // Returns -2
    minStackFree(minStack);
    return 0;
}

/*
Explanation:
Data Structures:
data: Stores the actual stack elements.
minData: Stores the minimum values corresponding to the elements in the main stack at each level.
top: Tracks the index of the top element in the stack.
capacity: Stores the maximum number of elements that can be held in the stack before resizing.
Functions:
minStackCreate: Initializes the MinStack with a specified capacity.
minStackPush: Pushes a value onto the stack. It also updates the min stack with the current minimum value.
minStackPop: Removes the top element from the stack.
minStackTop: Returns the top element of the stack.
minStackGetMin: Returns the minimum element in the stack.
minStackFree: Frees the allocated memory for the stack.
Usage:
The main function demonstrates the usage of the MinStack by pushing values, retrieving the minimum, popping the stack, and then checking the top and minimum values.
This implementation ensures all operations are performed in constant time, O(1), and dynamically resizes the stack when needed.
*/
