/*
Demonstrated the use of pthreads in matrix multiplication

Output:

 thread 0 created for row 0
 thread 1 created for row 1
 thread 2 created for row 2
Resulting matrix C (A x B):
50 60 
114 140 
178 220
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 100

// Define the matrices
int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
int numRowsA, numColsA, numRowsB, numColsB;

// Thread function to compute a single row of the resulting matrix
void* multiplyRow(void* arg) {
    int row = *(int*)arg;
    printf("\n thread %d created for row %d", row, row);
    free(arg);
    for (int j = 0; j < numColsB; j++) {
        C[row][j] = 0;
        for (int k = 0; k < numColsA; k++) {
            C[row][j] += A[row][k] * B[k][j];
        }
    }
    return NULL;
}

int main() {
    // Input dimensions of matrices
    printf("Enter dimensions of matrix A (rows cols): ");
    scanf("%d %d", &numRowsA, &numColsA);
    printf("Enter dimensions of matrix B (rows cols): ");
    scanf("%d %d", &numRowsB, &numColsB);

    // Validate matrix multiplication condition
    if (numColsA != numRowsB) {
        printf("Matrix multiplication not possible.\n");
        return -1;
    }

    // Input matrices A and B
    printf("Enter elements of matrix A:\n");
    for (int i = 0; i < numRowsA; i++) {
        for (int j = 0; j < numColsA; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter elements of matrix B:\n");
    for (int i = 0; i < numRowsB; i++) {
        for (int j = 0; j < numColsB; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    // Array of thread identifiers
    pthread_t threads[numRowsA];

    // Create threads to compute each row of the resulting matrix
    for (int i = 0; i < numRowsA; i++) {
        int* row = malloc(sizeof(int));
        *row = i;
        pthread_create(&threads[i], NULL, multiplyRow, row);
    }

    // Join threads
    for (int i = 0; i < numRowsA; i++) {
        pthread_join(threads[i], NULL);
    }

    // Output the resulting matrix
    printf("\nResulting matrix C (A x B):\n");
    for (int i = 0; i < numRowsA; i++) {
        for (int j = 0; j < numColsB; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}

