/*
Implement malloc free using static buffers (arrays)

Output:
Allocated 100 bytes.
Memory freed.
*/

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define BUFFER_SIZE 1024 // Size of the static buffer

static uint8_t buffer[BUFFER_SIZE]; // Static buffer for allocations
static bool free_map[BUFFER_SIZE];  // Bitmap to keep track of free/used blocks

// Initialize the memory allocator
void init_allocator() {
    for (size_t i = 0; i < BUFFER_SIZE; i++) {
        free_map[i] = true; // All blocks are initially free
    }
}

// Find a contiguous block of free memory of the required size
void* my_malloc(size_t size) {
    if (size == 0 || size > BUFFER_SIZE) {
        return NULL; // Invalid size
    }

    size_t required_blocks = (size + sizeof(size_t) - 1) / sizeof(size_t);
    size_t consecutive_free = 0;
    size_t start_index = 0;

    for (size_t i = 0; i < BUFFER_SIZE; i++) {
        if (free_map[i]) {
            if (consecutive_free == 0) {
                start_index = i;
            }
            consecutive_free++;
            if (consecutive_free == required_blocks) {
                // Allocate the block
                for (size_t j = start_index; j < start_index + required_blocks; j++) {
                    free_map[j] = false;
                }
                // Return pointer to allocated memory
                return buffer + start_index * sizeof(size_t);
            }
        } else {
            consecutive_free = 0;
        }
    }

    return NULL; // Not enough memory
}

// Free a previously allocated block of memory
void my_free(void* ptr) {
    if (ptr == NULL) {
        return; // Null pointer
    }

    size_t start_index = ((uint8_t*)ptr - buffer) / sizeof(size_t);
    size_t size = *(size_t*)(buffer + start_index * sizeof(size_t));

    size_t required_blocks = (size + sizeof(size_t) - 1) / sizeof(size_t);

    // Mark the block as free
    for (size_t i = start_index; i < start_index + required_blocks; i++) {
        free_map[i] = true;
    }
}

int main() {
    init_allocator();

    // Example usage
    size_t alloc_size = 100;
    void* ptr = my_malloc(alloc_size);

    if (ptr) {
        printf("Allocated %zu bytes.\n", alloc_size);

        // Free the allocated memory
        my_free(ptr);
        printf("Memory freed.\n");
    } else {
        printf("Failed to allocate memory.\n");
    }

    return 0;
}

