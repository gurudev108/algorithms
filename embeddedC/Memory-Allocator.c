/*

Output:
Free list after allocations:
Free block at 0x104dfc18e with size 626

Free list after freeing some blocks:
Free block at 0x104dfc000 with size 116
Free block at 0x104dfc074 with size 216
Free block at 0x104dfc18e with size 626

*/

#include <stdio.h>
#include <stddef.h> // for NULL and size_t

// Memory pool size
#define MEMORY_POOL_SIZE 1024  // 1 KB of memory pool

// Memory block structure
typedef struct MemoryBlock {
    size_t size;               // Size of the block (including the header)
    struct MemoryBlock* next;   // Pointer to the next free block
} MemoryBlock;

// Memory pool
static unsigned char memory_pool[MEMORY_POOL_SIZE];

// Pointer to the free list (start of the free blocks)
static MemoryBlock* free_list = NULL;

// Initialization function to set up the memory pool
void memory_init() {
    // Initially, the entire memory pool is one large free block
    free_list = (MemoryBlock*)memory_pool;
    free_list->size = MEMORY_POOL_SIZE;
    free_list->next = NULL;
}

// Simple malloc-like function
void* my_malloc(size_t size) {
    MemoryBlock* current = free_list;
    MemoryBlock* previous = NULL;

    // Add the size of the header to the requested size
    size_t total_size = size + sizeof(MemoryBlock);

    // First-fit algorithm to find a suitable block
    while (current != NULL) {
        if (current->size >= total_size) {
            // Found a suitable block
            if (current->size > total_size + sizeof(MemoryBlock)) {
                // Split the block into two, if it's larger than needed
                MemoryBlock* new_block = (MemoryBlock*)((unsigned char*)current + total_size);
                new_block->size = current->size - total_size;
                new_block->next = current->next;
                current->size = total_size;
                current->next = new_block;
            }

            // Remove the block from the free list
            if (previous == NULL) {
                free_list = current->next;
            } else {
                previous->next = current->next;
            }

            // Return the pointer to the memory after the header
            return (void*)((unsigned char*)current + sizeof(MemoryBlock));
        }

        // Move to the next block in the free list
        previous = current;
        current = current->next;
    }

    // No suitable block found
    return NULL;
}

// Simple free-like function
void my_free(void* ptr) {
    if (ptr == NULL) {
        return;
    }

    // Get the block header from the pointer
    MemoryBlock* block_to_free = (MemoryBlock*)((unsigned char*)ptr - sizeof(MemoryBlock));

    // Add the block back to the free list (at the start for simplicity)
    block_to_free->next = free_list;
    free_list = block_to_free;
}

// Debug function to print the free list
void print_free_list() {
    MemoryBlock* current = free_list;
    while (current != NULL) {
        printf("Free block at %p with size %zu\n", (void*)current, current->size);
        current = current->next;
    }
}

int main() {
    // Initialize the memory pool
    memory_init();

    // Print the free list after allocations
    printf("Free list before allocations of 100 200 50:\n");
    print_free_list();
    // Allocate memory blocks
    void* ptr1 = my_malloc(100);
    void* ptr2 = my_malloc(200);
    void* ptr3 = my_malloc(50);

    // Print the free list after allocations
    printf("Free list after allocations:\n");
    print_free_list();

    // Free some blocks
    my_free(ptr2);
    my_free(ptr1);

    // Print the free list after freeing
    printf("\nFree list after freeing some blocks:\n");
    print_free_list();

    return 0;
}

