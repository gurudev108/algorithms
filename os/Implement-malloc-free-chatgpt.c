/*

Implement malloc and free 

Approach:
manage memory using a simple free list approach. Here's the plan:

Buffer: A fixed-size array representing the available memory.
Free List: A linked list that tracks free memory blocks.
Allocation (mymalloc): Find a suitable free block and allocate memory from it.
Deallocation (myfree): Return a block of memory to the free list.

Output:
Block at 0x102c80000, size: 1008
After allocations:
Block at 0x102c8018e, size: 610
After freeing p2:
Block at 0x102c80074, size: 200
Block at 0x102c8018e, size: 610
After allocating 150 bytes:
Block at 0x102c8011a, size: 34
Block at 0x102c8018e, size: 610
After freeing all allocations:
Block at 0x102c80074, size: 150
Block at 0x102c8014c, size: 50
Block at 0x102c80000, size: 100
Block at 0x102c8011a, size: 34
Block at 0x102c8018e, size: 610
*/

#include <stdio.h>
#include <stddef.h>

#define BUFFER_SIZE 1024

// Define a block structure
typedef struct Block {
    size_t size;         // Size of the block
    struct Block* next;  // Pointer to the next block in the free list
} Block;

// Define the buffer
static char buffer[BUFFER_SIZE];

// Pointer to the head of the free list
static Block* free_list;

// Initialize the free list with the entire buffer
void mymalloc_init() {
    free_list = (Block*)buffer;
    free_list->size = BUFFER_SIZE - sizeof(Block);
    free_list->next = NULL;
}

// Allocate memory
void* mymalloc(size_t size) {
    Block* current = free_list;
    Block* previous = NULL;

    while (current != NULL) {
        // Check if the current block is big enough
        if (current->size >= size) {
            // Check if we can split the block
            if (current->size > size + sizeof(Block)) {
                // Splitting Current - Insert new block after current
                Block* new_block = (Block*)((char*)current + sizeof(Block) + size);
                new_block->size = current->size - size - sizeof(Block);
                new_block->next = current->next;

                current->size = size;
                if (previous != NULL) {
                    previous->next = new_block;
                } else {
                    free_list = new_block;
                }
            } else {
                // Can't split, use the entire block
                if (previous != NULL) {
                    previous->next = current->next;
                } else {
                    free_list = current->next;
                }
            }
            return (void*)((char*)current + sizeof(Block));
        }

        // Move to the next block in the free list
        previous = current;
        current = current->next;
    }

    // No suitable block found
    return NULL;
}

// Free memory
void myfree(void* ptr) {
    if (ptr == NULL) {
        return;
    }

    Block* block = (Block*)((char*)ptr - sizeof(Block));
    block->next = free_list;
    free_list = block;
}

// Print the free list (for debugging)
void print_free_list() {
    Block* current = free_list;
    while (current != NULL) {
        printf("Block at %p, size: %zu\n", (void*)current, current->size);
        current = current->next;
    }
}

int main() {
    // Initialize the custom allocator
    mymalloc_init();

    print_free_list();

    // Allocate some memory
    void* p1 = mymalloc(100);
    void* p2 = mymalloc(200);
    void* p3 = mymalloc(50);

    printf("After allocations:\n");
    print_free_list();

    // Free some memory
    myfree(p2);
    printf("After freeing p2:\n");
    print_free_list();

    void* p4 = mymalloc(150);
    printf("After allocating 150 bytes:\n");
    print_free_list();

    // Free remaining allocations
    myfree(p1);
    myfree(p3);
    myfree(p4);
    printf("After freeing all allocations:\n");
    print_free_list();

    return 0;
}

/*
Explanation

Initialization (mymalloc_init):
The entire buffer is initially free, so we set up a single large free block.

Allocation (mymalloc):
We search the free list for a block large enough to satisfy the allocation request.
If a suitable block is found, we check if it can be split. If the remaining space after allocation is large enough
for a new block, we split the block and adjust the free list.
Otherwise, we allocate the entire block.

Deallocation (myfree):
The deallocated block is added back to the free list. This simple implementation doesn't coalesce adjacent free blocks.

Printing Free List (print_free_list):
This function prints the state of the free list for debugging and verification purposes.
*/