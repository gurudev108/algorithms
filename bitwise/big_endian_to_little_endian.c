/*
Output: 
Big-endian: 0x12345678
Little-endian: 0x78563412
*/
#include <stdio.h>

// Function to convert a big-endian integer to a little-endian integer
unsigned int convertEndian(unsigned int bigEndian) {
    // Extract individual bytes
    unsigned char byte1 = (bigEndian >> 24) & 0xFF;
    unsigned char byte2 = (bigEndian >> 16) & 0xFF;
    unsigned char byte3 = (bigEndian >> 8) & 0xFF;
    unsigned char byte4 = bigEndian & 0xFF;

    // Create the little-endian integer by swapping the order of bytes
    unsigned int littleEndian = (byte4 << 24) | (byte3 << 16) | (byte2 << 8) | byte1;

    return littleEndian;
}

int main() {
    // Example usage
    unsigned int bigEndianValue = 0x12345678; // Example big-endian value

    // Convert to little-endian
    unsigned int littleEndianValue = convertEndian(bigEndianValue);

    // Display the results
    printf("Big-endian: 0x%08X\n", bigEndianValue);
    printf("Little-endian: 0x%08X\n", littleEndianValue);

    return 0;
}

