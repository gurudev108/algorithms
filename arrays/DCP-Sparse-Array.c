/*
Daily Coding Problem: Problem #588 [Easy]
This problem was asked by Facebook.

You have a large array with most of the elements as zero.

Use a more space-efficient data structure, SparseArray, that implements the same interface:

init(arr, size): initialize with the original large array and size.
set(i, val): updates index at i with val.
get(i): gets the value at index i.

Approach - use a hashmap to store only non zero values. 
This C implementation of SparseArray stores non-zero values and their indices in parallel arrays. 
The set function updates or adds entries for non-zero values and removes entries for zeros. 
The get function retrieves values for a given index. 
Be sure to free the memory with freeSparseArray when you're done with the SparseArray.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int* values;
    int* indices;
    int count;
} SparseArray;

SparseArray* init(int size) {
    SparseArray* sparseArray = (SparseArray*)malloc(sizeof(SparseArray));
    sparseArray->size = size;
    sparseArray->values = (int*)malloc(size * sizeof(int));
    sparseArray->indices = (int*)malloc(size * sizeof(int));
    sparseArray->count = 0;

    return sparseArray;
}

void set(SparseArray* sparseArray, int i, int val) {
    if (i < 0 || i >= sparseArray->size) {
        printf("Index out of range\n");
        return;
    }

    int found = 0;
    for (int j = 0; j < sparseArray->count; j++) {
        if (sparseArray->indices[j] == i) {
            sparseArray->values[j] = val;
            found = 1;
            if (val == 0) {
                // Remove the entry
                for (int k = j; k < sparseArray->count - 1; k++) {
                    sparseArray->indices[k] = sparseArray->indices[k + 1];
                    sparseArray->values[k] = sparseArray->values[k + 1];
                }
                sparseArray->count--;
            }
            break;
        }
    }

    if (!found && val != 0) {
        // Add a new entry
        sparseArray->indices[sparseArray->count] = i;
        sparseArray->values[sparseArray->count] = val;
        sparseArray->count++;
    }
}

int get(SparseArray* sparseArray, int i) {
    if (i < 0 || i >= sparseArray->size) {
        printf("Index out of range\n");
        return 0;
    }

    for (int j = 0; j < sparseArray->count; j++) {
        if (sparseArray->indices[j] == i) {
            return sparseArray->values[j];
        }
    }

    return 0;
}

void freeSparseArray(SparseArray* sparseArray) {
    free(sparseArray->values);
    free(sparseArray->indices);
    free(sparseArray);
}

int main() {
    int size = 10;
    SparseArray* sparseArray = init(size);

    set(sparseArray, 3, 4);
    printf("%d\n", get(sparseArray, 3));  // Output: 4

    set(sparseArray, 8, 7);
    printf("%d\n", get(sparseArray, 8));  // Output: 7

    set(sparseArray, 10, 5); // Index out of range
    printf("%d\n", get(sparseArray, 10));  // Output: 0 (out of range)

    freeSparseArray(sparseArray);

    return 0;
}

