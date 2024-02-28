/* 
* A very large number (more than 64 bits) is represented as an array with each element size of a byte. 
* Implement a function that will right shift the large number represented as an array.
* Example 0x1001 represented as arr= [0x10, 0x01], arr_size = 2.
* If num_bits_to_shift is 1, 0x1001>>1 = 0x0800. arr = [0x08, 0x00]
*/

#include <stdio.h>
#include <stdint.h>

typedef unsigned char BYTE

void shift_right(BYTE* byte_arr, uint32_t arr_size, uint32_t num_bits_to_shift)
{

}
