#include <stddef.h>

void *memmove(void *dest, const void *src, size_t n) {
    unsigned char *d = dest;
    const unsigned char *s = src;

    if (d == s) {
        // Nothing to do if source and destination are the same.
        return dest;
    }

    if (d < s || d >= s + n) {
        // Non-overlapping buffers, can use memcpy.
        while (n--) {
            *d++ = *s++;
        }
    } else {
        // Overlapping buffers, use reverse copy.
        d += n;
        s += n;

        while (n--) {
            *(--d) = *(--s);
        }
    }

    return dest;
}

