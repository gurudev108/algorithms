/* 

Input: 18 0010010
Output:
The rightmost bit set to 1 in number 18 n&-n=2 is at position: 1
*/
#include <stdio.h>
#include <stdint.h>

uint32_t rightmostSetBit(uint32_t n) {
    return n & (-n);  //### or n & ~(n-1);
}



int main() {
    uint32_t num = 18; // Binary representation: 10010
    uint32_t result = rightmostSetBit(num);
    
    // Print the position of the rightmost set bit.
    if (result) {
        printf("The rightmost bit set to 1 in number %u n&-n=%d is at position: %d\n", num, result, __builtin_ctz(result));
    } else {
        printf("The number %u has no set bits.\n", num);
    }

    return 0;
}

