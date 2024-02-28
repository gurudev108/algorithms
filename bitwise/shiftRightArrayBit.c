/*
A very large number (greater than 64 bits) is represented as an array with each element size of a BYTE.
Implement a function that'll right shift the large number represented as an array.
Example - 0x1001 represented as arr=[0x10, 0x01], arr_size=2
If num_bits_to_shift is 1, 0x1001 >> 1 = 0x0800, arr=[0x08, 0x00]
*/

#include <stdio.h>
#include <stdint.h>
typedef unsigned char BYTE;

void shift_right(BYTE* byte_arr, uint32_t arr_size, uint32_t num_bits_to_shift)
{
  int mask = (1<<num_bits_to_shift)-1;
  int carry = 0;
  for (int i=0; i<arr_size; i++)
  {
    if(num_bits_to_shift < 8)
    {
      printf("\nbyte_arr[%d] = 0x%x", i, byte_arr[i]);
      byte_arr[i] = byte_arr[i]>>num_bits_to_shift;
      printf("\nbyte_arr[%d] after shifting %d = 0x%x", i, num_bits_to_shift, byte_arr[i]);
      byte_arr[i] |= (carry <<(8-num_bits_to_shift)); 
      printf("\nbyte_arr[%d] after | with carry = 0x%x", i, byte_arr[i]);
      carry = byte_arr[i] & mask;
      printf("\ncarry=%d", carry);
//      carry = byte_arr[i]<<(8-num_bits_to_shift);
//      byte_arr[i] >>= num_bits_to_shift;
    }

  }
}

int main()
{
  BYTE byte_arr[] = {0x03, 0x01};
  shift_right(byte_arr, 2, 2);
  printf("Result - 0x%x 0x%x", byte_arr[0], byte_arr[1]);
  return 0;
}

