/*

Sure, let's create a basic implementation of Hamming code for error detection and correction. For simplicity, 
let's consider a 7-bit Hamming code (4 data bits and 3 parity bits). Here's a brief overview:

1. We will have 7 bits in total: `p1`, `p2`, `d1`, `p3`, `d2`, `d3`, `d4` where `p` are parity bits and `d` are data bits.
2. The parity bits are calculated as follows:
   - `p1` checks bits: 1, 3, 5, 7
   - `p2` checks bits: 2, 3, 6, 7
   - `p3` checks bits: 4, 5, 6, 7

Here's the C code for encoding and decoding using Hamming(7,4):

This program first encodes the data bits with Hamming(7,4), introduces an error in the encoded data, and then detects and corrects the error during decoding.


Certainly! Let's break down the Hamming code, specifically the Hamming(7,4) code, which means 7 bits in the code with 4 of them being data bits and 3 being parity bits.

### Positioning of Parity Bits:

###IMP - The parity bits are placed in positions that are powers of 2. That is, positions 1, 2, 4, 8, ... (remembering that we start indexing from 1, not 0).

In our case with Hamming(7,4):
- Bit 1 is `p1` (parity bit)
- Bit 2 is `p2` (parity bit)
- Bit 3 is `d1` (data bit)
- Bit 4 is `p3` (parity bit)
- Bit 5 is `d2` (data bit)
- Bit 6 is `d3` (data bit)
- Bit 7 is `d4` (data bit)

### Calculating Parity Bits:

Each parity bit checks certain positions, determining whether the number of 1s in those positions is even or odd. 
If odd, the parity bit is set to 1; if even, it's set to 0. The positions each parity bit checks are determined by its position (power of 2).

- `p1` checks positions: 1, 3, 5, 7
- `p2` checks positions: 2, 3, 6, 7
- `p3` checks positions: 4, 5, 6, 7

This system of checks is designed so that each data bit is checked by a unique combination of parity bits. 
This way, when there's a single error, the pattern of which parity bits are "wrong" uniquely identifies the error's location.

### Error Detection and Correction:

When the receiver gets the encoded message, it recalculates the parity bits based on the received data and parity bits. 
It then compares the calculated parity bits with the received ones:

- The recalculated `p1` is XOR'd with the received `p1` to get a new `p1`.
- The recalculated `p2` is XOR'd with the received `p2` to get a new `p2`.
- And so on...

This process results in an error vector:
`error = p1*1 + p2*2 + p3*4`

If all parity bits match, `error` will be 0, and no errors are detected. If `error` is non-zero, it indicates the position of the erroneous bit. 
Since each bit is covered by a unique combination of parity bits, each possible value of the error vector corresponds to a unique bit position.

### Why XOR?

XOR (exclusive or) is a binary operation that outputs true (or 1) only when an odd number of inputs are true. 
If we apply XOR to a group of bits, the result will be 1 if the number of 1s in the group is odd and 0 otherwise. 
This property makes XOR a natural choice for generating parity bits in error-checking algorithms like Hamming code.

In the code provided:
- The parity bits are calculated using XOR to ensure even parity.
- When checking for errors, XOR is again used on the received message to determine if the received and calculated parity bits match.

That's a brief overview of the logic behind the Hamming(7,4) code in the provided program!

*/


#include <stdio.h>

void encode(int data[4], int encoded[7]) {
    // Set data bits
    encoded[2] = data[0];
    encoded[4] = data[1];
    encoded[5] = data[2];
    encoded[6] = data[3];
    
    // Calculate parity bits
    encoded[0] = encoded[2] ^ encoded[4] ^ encoded[6];
    encoded[1] = encoded[2] ^ encoded[5] ^ encoded[6];
    encoded[3] = encoded[4] ^ encoded[5] ^ encoded[6];
}

int decode(int encoded[7]) {
    int error = 0;
    
    int p1 = encoded[0] ^ encoded[2] ^ encoded[4] ^ encoded[6];
    int p2 = encoded[1] ^ encoded[2] ^ encoded[5] ^ encoded[6];
    int p3 = encoded[3] ^ encoded[4] ^ encoded[5] ^ encoded[6];

    error = p1 * 1 + p2 * 2 + p3 * 4;

    if (error) {
        printf("Error detected at position %d\n", error);
        // Correct the error
        encoded[error - 1] ^= 1;
    } else {
        printf("No error detected.\n");
    }
    
    return error;
}

int main() {
    int data[4] = {1, 0, 1, 1};
    int encoded[7] = {0};
    
    printf("Original Data: ");
    for(int i = 0; i < 4; i++)
        printf("%d ", data[i]);
    printf("\n");
    
    encode(data, encoded);

    printf("Encoded Data: ");
    for(int i = 0; i < 7; i++)
        printf("%d ", encoded[i]);
    printf("\n");
    
    // Introduce an error for testing
    encoded[4] ^= 1;
    
    printf("Received Data (with error): ");
    for(int i = 0; i < 7; i++)
        printf("%d ", encoded[i]);
    printf("\n");

    decode(encoded);

    printf("Corrected Data: ");
    for(int i = 0; i < 7; i++)
        printf("%d ", encoded[i]);
    printf("\n");
    
    return 0;
}

