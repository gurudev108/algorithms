#include <stdio.h>

size_t alignToPointerSize(size_t size) {
    // Ensure that the size is aligned to the size of a pointer
    size = (size + sizeof(void*) - 1) & ~(sizeof(void*) - 1);
    return size;
}

int main() {
    size_t originalSize, alignedSize;

    // Take input for the original size
    printf("Enter the size of memory you want to allocate: ");
    scanf("%zu", &originalSize);

    // Calculate the aligned size
    alignedSize = alignToPointerSize(originalSize);

    // Display the results
    printf("Original Size: %zu\n", originalSize);
    printf("Aligned Size: %zu\n", alignedSize);

    return 0;
}

