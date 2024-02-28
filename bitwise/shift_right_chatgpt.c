/* Explanation
* When we perform a right shift, the least significant bits (closer to the LSB) are the first ones affected. As the number of shifts increase, this "effect" ripples
 upwards toward the more significant bits (closer to the MSB). So, starting the shift operation from the LSB ensures that this ripple effect is correctly implemented 
 across the byte array.

* Here's a step-by-step explanation of the code:

* Step 1 - Checking if num_bits_to_shift exceeds total bits:
* If the number of bits to shift is larger than the total number of bits in the array, we set the entire array to zero.

* Step 2- Calculating Byte and Bit Shifts:
* byte_shifts: It calculates the total number of complete bytes over which the shift needs to happen.
* bit_shifts: The residual bits that need to be shifted once the complete byte shifts are done.

* Step 3- Iterating over the byte array:
* The loop starts from the end (LSB) and moves towards the start (MSB) of the byte array.
* Within this loop, the program handles shifting for two cases: whole byte shifts and then individual bit shifts.

* Step 3.1 Whole Byte Shifts (byte_shifts):
* - If the current byte position minus byte_shifts goes negative, it means that the current byte (and all bytes before it) will become zero after the shift.
* - If not, we take the value from byte_arr[i - byte_shifts] and assign it to the current byte, effectively moving the byte values to the right.

* Step 3.2 Residual Bit Shifts (bit_shifts):
* - This is where the ripple effect is visible.
* - For each byte, we shift it to the right by the required number of bits.
* - To ensure the continuity of data, we also take the bits from the next byte (i.e., byte_arr[i - 1]), shift them to the left to position them correctly, and then OR them with the current byte. This action ensures that the lost bits from the right shift of the current byte are filled with the corresponding bits from the next byte.
* Starting the loop from the LSB ensures that this "filling" of bits from the adjacent byte happens correctly. If you were to start from the MSB, you'd need to keep track of lost bits and then use them in the next iterations, complicating the logic.

*/
#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

void shift_right(BYTE* byte_arr, uint32_t arr_size, uint32_t num_bits_to_shift) {
    if (num_bits_to_shift >= arr_size * 8) {
        // If the number of bits to shift is larger than the total number of bits,
        // set all bytes to zero.
        for (uint32_t i = 0; i < arr_size; i++) {
            byte_arr[i] = 0;
        }
        return;
    }

    uint32_t byte_shifts = num_bits_to_shift / 8;
    uint32_t bit_shifts = num_bits_to_shift % 8;

    /* ## IMP TIP - easier to start loop from the LSB, from MSB gets complicated */
    for (int32_t i = arr_size - 1; i >= 0; i--) {
        // Handle the shift for whole bytes
        if (i - byte_shifts < 0) {
            byte_arr[i] = 0;
        } else {
            //IMP
            byte_arr[i] = byte_arr[i - byte_shifts];
        }

        // Handle the residual bit shifts
        if (bit_shifts > 0) {
            //IMP
            byte_arr[i] >>= bit_shifts;
            if (i - 1 >= 0) {
    // ## IMP how to handle the carry
                byte_arr[i] |= byte_arr[i - 1] << (8 - bit_shifts);
            }
        }
    }
}

int main() {
    BYTE arr[] = {0x10, 0x01};
    uint32_t arr_size = sizeof(arr) / sizeof(BYTE);
    uint32_t num_bits_to_shift = 1;

    shift_right(arr, arr_size, num_bits_to_shift);

    printf("Shifted Array: ");
    for (uint32_t i = 0; i < arr_size; i++) {
        printf("0x%02X ", arr[i]);
    }

    return 0;
}

