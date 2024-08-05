/*


Sure! Let's extend each of the examples with a function call to perform an operation on the matrices, such as printing the matrix. The functions will demonstrate how to pass the matrices to functions and access their elements.

### 1. **Static Initialization with Fixed-Size 2D Arrays**

In this case, we pass the matrix dimensions along with the matrix itself.

#### Code
*/
#include <stdio.h>
#include <stdlib.h>

void printMatrix1(int rows, int cols, int mat[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main1() {
    int mat1[2][3] = {
        {1, 0, 0},
        {-1, 0, 3}
    };

    printMatrix1(2, 3, mat1);

    return 0;
}
/*

### 2. **Dynamic Allocation with Pointers**

Here, we pass a pointer to an array of pointers and the matrix dimensions.

#### Code
*/

void printMatrix2(int rows, int cols, int** mat) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main2() {
    int rows1 = 112, cols1 = 3;

    int** mat1 = (int**)malloc(rows1 * sizeof(int*));
    for (int i = 0; i < rows1; i++) {
        mat1[i] = (int*)malloc(cols1 * sizeof(int));
    }

    mat1[0][0] = 1; mat1[0][1] = 0; mat1[0][2] = 0;
    mat1[1][0] = -1; mat1[1][1] = 0; mat1[1][2] = 3;

    printMatrix2(rows1, cols1, mat1);

    for (int i = 0; i < rows1; i++) {
        free(mat1[i]);
    }
    free(mat1);

    return 0;
}
/*

### 3. **Using a Single Contiguous Block of Memory**

The matrix is passed as a single pointer along with the number of rows and columns.

#### Code
*/

void printMatrix3(int rows, int cols, int* mat) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", *(mat + i * cols + j));
        }
        printf("\n");
    }
}

int main3() {
    int rows1 = 2, cols1 = 3;

    int* mat1 = (int*)malloc(rows1 * cols1 * sizeof(int));

    mat1[0 * cols1 + 0] = 1;
    mat1[0 * cols1 + 1] = 0;
    mat1[0 * cols1 + 2] = 0;
    mat1[1 * cols1 + 0] = -1;
    mat1[1 * cols1 + 1] = 0;
    mat1[1 * cols1 + 2] = 3;

    printMatrix3(rows1, cols1, mat1);

    free(mat1);

    return 0;
}
/*

### 4. **Using Variable Length Arrays (VLAs)**

In this case, the matrix and its dimensions are passed directly.

#### Code
*/

void printMatrix4(int rows, int cols, int mat[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main4() {
    int rows1 = 2, cols1 = 3;

    int mat1[rows1][cols1];

    mat1[0][0] = 1;
    mat1[0][1] = 0;
    mat1[0][2] = 0;
    mat1[1][0] = -1;
    mat1[1][1] = 0;
    mat1[1][2] = 3;

    printMatrix4(rows1, cols1, mat1);

    return 0;
}

int main()
{
  printf("\nMain1\n");
  main1();
  printf("\nMain2\n");
  main2();
  printf("\nMain3\n");
  main3();
  printf("\nMain4\n");
  main4();
}
/*

### Summary

- **Fixed-Size 2D Arrays**: The function accepts the matrix dimensions and the matrix as `int mat[rows][cols]`.
- **Dynamic Allocation with Pointers**: The function accepts the matrix dimensions and a double pointer `int** mat`.
- **Single Contiguous Block of Memory**: The function accepts the matrix dimensions and a single pointer `int* mat`. Access is done using pointer arithmetic.
- **Variable Length Arrays (VLAs)**: The function accepts the matrix dimensions and the matrix as `int mat[rows][cols]`.

Each method has its own way of passing and accessing the matrix elements, depending on whether the matrix is statically allocated, dynamically allocated, or stored in a single contiguous memory block.
*/
