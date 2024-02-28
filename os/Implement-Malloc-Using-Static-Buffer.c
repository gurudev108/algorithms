/*

To implement malloc and free using static buffers (arrays), you can create a simple memory allocator that manages a fixed-size block of memory.
The malloc function will allocate memory from the static buffer, and the free function will release the allocated memory. Here's a basic example:

In this example, initializeAllocator initializes the memory allocator, myMalloc allocates memory, and myFree frees allocated memory. 
The printFreeBlocks function is provided for testing purposes to print the state of free blocks in the allocator.

Note that this is a very basic and naive implementation for educational purposes. In a real-world scenario, a memory allocator needs to handle 
concurrency, fragmentation, and other considerations, which are beyond the scope of this simple example. Additionally, this implementation assumes 
a single block of memory, and it does not handle memory leaks or other advanced features.
*/

#include <stdio.h>
#include <stddef.h>

#define MEMORY_SIZE 1024 // Adjust the size based on your needs

// Static memory buffer
static char memory[MEMORY_SIZE];

// Node structure for maintaining free memory blocks
struct FreeBlock {
    size_t size;
    struct FreeBlock* next;
};

// Pointer to manage the start of the free list
static struct FreeBlock* freeList;

// Function to initialize the memory allocator
void initializeAllocator() {
    freeList = (struct FreeBlock*)memory;
    freeList->size = MEMORY_SIZE - sizeof(struct FreeBlock);
    freeList->next = NULL;
}

// Function to allocate memory
void* myMalloc(size_t size) {
    struct FreeBlock *prev, *current;
    void* result = NULL;

    /* ##IMP format specifier to print size_t is zu */
    /* ##IMP MEMORY SIZE ALIGNMENT */
    printf("\nmyMalloc called to allocate size %zu", size);
    size = (size + sizeof(void*) - 1) & ~(sizeof(void*) - 1);
    printf("\nmyMalloc adjusted size %zu after memory alignment", size);


    // Traverse the free list to find a suitable block
    prev = NULL;
    current = freeList;
    int index = 0;
    while (current != NULL) {
        if (current->size >= size) {
            if (current->size > size + sizeof(struct FreeBlock)) {
                // Split the block if it's larger than needed
                struct FreeBlock* newBlock = (struct FreeBlock*)((char*)current + size + sizeof(struct FreeBlock));
                newBlock->size = current->size - size - sizeof(struct FreeBlock);
                newBlock->next = current->next;
                current->size = size;
                current->next = newBlock;
            }

            if (prev == NULL) {
                // Adjust the start of the free list
                if (current->next != NULL) {
                    freeList = current->next;
                } else {
                    freeList = NULL; // No more free blocks
                }
            } else {
                // Remove the block from the free list
                prev->next = current->next;
            }

            result = (char*)current + sizeof(struct FreeBlock);
            break;
        }

        prev = current;
        current = current->next;
        printf("\nmalloc While loop index %d", index++);
    }

    return result;
}

// Function to free allocated memory
void myFree(void* ptr) {
    if (ptr == NULL) {
        return; // Do nothing if NULL is passed
    }

    // Add the freed block to the free list
    struct FreeBlock* newFreeBlock = (struct FreeBlock*)((char*)ptr - sizeof(struct FreeBlock));
    newFreeBlock->size = newFreeBlock->size + sizeof(struct FreeBlock);
    newFreeBlock->next = freeList;
    freeList = newFreeBlock;
}

// Function to print the free blocks (for testing purposes)
void printFreeBlocks() {
    struct FreeBlock* current = freeList;
    int index = 0;
    while (current != NULL) {
        printf("\n%d. Free Block: Size = %zu", index++, current->size);
        current = current->next;
    }
}

int main() {
    // Initialize the memory allocator
    initializeAllocator();

    printf("Free Blocks (Before Allocation):\n");
    printFreeBlocks();

    // Allocate memory
    int* arr1 = (int*)myMalloc(5 * sizeof(int));

    printf("\nFree Blocks (After 5 int Allocation):\n");
    printFreeBlocks();

    double* arr2 = (double*)myMalloc(3 * sizeof(double));
    printf("\nFree Blocks (After 3 double Allocation):\n");
    printFreeBlocks();


    // Free memory
    myFree(arr1);

    // Print the free blocks (after freeing memory)
    printf("\nFree Blocks (After Freeing Memory):\n");
    printFreeBlocks();

    // Allocate memory
    int* arr3 = (int*)myMalloc(2 * sizeof(int));
    printFreeBlocks();

    // Allocate memory
    int* arr4 = (int*)myMalloc(8 * sizeof(int));
    printFreeBlocks();

    return 0;
}

