/*
Next high power of 8

Adding 7 to the number ensures that any number in a range that is not already a multiple of 8 will round up. For example, if num is 9, adding 7 gives 16, which is the next multiple of 8.
The bitwise AND with ~7 clears the last three bits, effectively rounding down to the nearest multiple of 8 after adding 7. The value ~7 is a bitmask with all bits set except the last three, which correspond to the binary representation of 7.
*/

#include <stdio.h>

// Function to round a number up to the next higher multiple of 8
int roundToNextMultipleOf8(int num) {
    return (num + 7) & ~7;
}

// Example usage
int main() {
    int num;
    
    printf("Enter a number: ");
    scanf("%d", &num);
    
    int roundedNum = roundToNextMultipleOf8(num);
    printf("Number rounded up to the next multiple of 8: %d\n", roundedNum);

    return 0;
}

