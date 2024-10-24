/*
The memcpy function does not handle overlapping memory regions correctly. If the source and destination regions overlap, 
using memcpy can lead to undefined behavior because it does not account for the order of copying. 
Data can be overwritten before it has been copied, resulting in corrupted output.
For scenarios where the source and destination memory regions may overlap, you should use memmove. 
The memmove function is designed to handle such cases safely. It checks the relative positions of the source and 
destination pointers and chooses whether to copy the data forwards or backwards to avoid overwriting the source data.
*/

#include <stdio.h>

// Custom memmove function
void* my_memmove(void* dest, const void* src, size_t n) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;

    if (d == s || n == 0) {
        return dest;
    }

    if (d < s) {
        // Copy from beginning to end
        for (size_t i = 0; i < n; i++) {
            d[i] = s[i];
        }
    } else {
        // Copy from end to beginning to avoid overwriting
        for (size_t i = n; i > 0; i--) {
            d[i - 1] = s[i - 1];
        }
    }

    return dest;
}

// Example usage
int main() {
    char str[] = "Hello, world!";
    printf("Original string: %s\n", str);

    // Use custom memmove to copy "world" to the start of the string
    my_memmove(str, str + 7, 5);
    str[5] = '\0'; // Null-terminate the result
    printf("After my_memmove: %s\n", str);

    return 0;
}
