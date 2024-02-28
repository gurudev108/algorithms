#include <stdio.h>

void *my_memcpy(void *dest, const void *src, size_t n) {
    char *dest_ptr = (char *)dest;
    const char *src_ptr = (const char *)src;
    size_t i;
    // Copy each byte from source to destination
    for (i = 0; i < n; i++) {
        dest_ptr[i] = src_ptr[i];
    }
    dest_ptr[++i] = '\0';
    return dest;
}

int main() {
    // Example usage
    const char source[] = "Hello, World!";
    char destination[20];

    // Copy 13 bytes from source to destination
    my_memcpy(destination, source, 13);

    // Print the result
    printf("Copied String: %s\n", destination);

    return 0;
}

