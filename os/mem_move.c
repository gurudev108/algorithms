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
