/*
DOES NOT HANDLE OVERLAPPING MEMORY REGIONS - Use memmove instead.
The memcpy function does not handle overlapping memory regions correctly. If the source and destination regions overlap, 
using memcpy can lead to undefined behavior because it does not account for the order of copying. 
Data can be overwritten before it has been copied, resulting in corrupted output.
For scenarios where the source and destination memory regions may overlap, you should use memmove. 
The memmove function is designed to handle such cases safely. It checks the relative positions of the source and 
destination pointers and chooses whether to copy the data forwards or backwards to avoid overwriting the source data.
*/
#include <stdio.h>
#include <string.h>

// Custom memcpy function
void* my_memcpy(void* dest, const void* src, size_t n) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;

    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }

    return dest;
}

// Example usage
int main() {
    char src[] = "Hello, world!";
    char dest[20];

    /* If you're copying raw data (not strings), you don't need to worry about null-terminating characters.
    However, when copying strings, ensuring the null terminator is included is essential to avoid issues 
    like buffer overruns or incorrect string handling.
    */
    // Use custom memcpy to copy the string, including the null terminator
    my_memcpy(dest, src, strlen(src) + 1);

    printf("Source: %s\n", src);
    printf("Destination: %s\n", dest);

    return 0;
}
