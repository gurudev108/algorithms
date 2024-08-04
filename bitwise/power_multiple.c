#include <stdio.h>

/* Function to check if a number is a power of 2. A number that is a power of 2 has exactly one bit set in its binary representation.
A number n is a power of 2 if n & (n - 1) == 0 and n is greater than zero. This is because, for numbers that are powers of 2, their binary representation has exactly one bit set, and subtracting 1 from them flips all bits after the set bit (including the set bit).
*/
int isPowerOfTwo(unsigned int n) {
    // Check if n is greater than 0 and n & (n - 1) is 0
    return (n != 0) && ((n & (n - 1)) == 0);
}

/*
A number n is a power of 4 if the following conditions are met. 
a) There is only one bit set in the binary representation of n (or n is a power of 2) 
b) The count of zero bits before the (only) set bit is even.
For example 16 (10000) is the power of 4 because there is only one bit set and count of 0s before the set bit is 4 which is even.
*/
int isPowerOf4(int num) {
    // Check if it is a power of 2 and the set bit is at an even position
    return (num > 0) && ((num & (num - 1)) == 0) && ((num & 0xAAAAAAAA) == 0);
}

int isMultipleOf4(int num) {
    // Check if the last two bits are zeros
    return (num & 3) == 0;
}

/*
A number is a power of 8 if the following conditions are satisfied. 

a) The number is the power of two. A number is the power of two if it has only one set bit, i.e., bitwise and of n and n-1 is 0.
b) The number has its only set bit at position 0 or 3 or 6 or …. 30 [For a 32-bit number]. To check the position of its set bit we can use a mask (0xB6DB6DB6)16 = (10110110110110110110110110110110)2.
*/

int isPowerOf8(int num) {
    // Check if it is a power of 2 and the set bit is in the correct position
    return (num > 0) && ((num & (num - 1)) == 0) && ((num & 0xB6DB6DB6) == 0);
}

int isMultipleOf8(int num) {
    // Check if the last three bits are zeros
    return (num & 7) == 0;
}

int isPowerOf4Or8(int num) {
    // Check if it is a power of 2
    if (num <= 0 || (num & (num - 1)) != 0) {
        return 0; // Not a power of 2
    }

    // Check if the set bit is in the correct position for power of 4 or 8
    if ((num & 0xAAAAAAAA) == 0) {
        // Set bit is in an even position (power of 4)
        printf("%d is a power of 4.\n", num);
    } else if ((num & 0x80000000) == 0) {
        // Set bit is in the most significant position (power of 8)
        printf("%d is a power of 8.\n", num);
    } else {
        // Other cases
        printf("%d is not a power of 4 or 8.\n", num);
    }

    return 1; // Success
}

int main() {
    int number;

    // Input value
    printf("Enter a number: ");
    scanf("%d", &number);

    // Check if the number is a power of 4 and print the result
    if (isPowerOf4(number)) {
        printf("%d is a power of 4.\n", number);
    } else {
        printf("%d is not a power of 4.\n", number);
    }

    return 0;
}

