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
