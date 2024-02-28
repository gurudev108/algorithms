#include <stdio.h>

// Function to shift data in an 8-bit shift register
void shiftRegister(unsigned char *registerState, unsigned char data) {
    // Shift existing bits to the left
    *registerState <<= 1;
    // Set the rightmost bit with the new data
    *registerState |= (data & 0x01);
}

int main() {
    unsigned char shiftRegisterState = 0; // Initial state of the shift register

    // Simulate shifting in 8 bits of data
    unsigned char inputData[] = {1, 0, 1, 0, 1, 1, 0, 0};

    for (int i = 0; i < 8; ++i) {
        shiftRegister(&shiftRegisterState, inputData[i]);
        printf("Shift Register State: 0x%02X\n", shiftRegisterState);
    }

    return 0;
}

