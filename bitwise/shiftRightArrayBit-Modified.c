/*
A very large number (greater than 64 bits) is represented as an array with each element size of a BYTE.
Implement a function that'll right shift the large number represented as an array.
Example - 0x1001 represented as arr=[0x10, 0x01], arr_size=2
If num_bits_to_shift is 1, 0x1001 >> 1 = 0x0800, arr=[0x08, 0x00]
*/

#include <stdio.h>
#include <stdint.h>
typedef unsigned char BYTE;
/*
void shift_right(BYTE* byte_arr, uint32_t arr_size, uint32_t num_bits_to_shift)
{
  int mask = (1<<num_bits_to_shift)-1;
  int carry = 0;
  for (int i=0; i<arr_size; i++)
  {
    if(num_bits_to_shift < 8)
    {
      printf("\nbyte_arr[%d] = 0x%x", i, byte_arr[i]);
      carry = byte_arr[i] & mask;
      byte_arr[i] = byte_arr[i]>>num_bits_to_shift;
      printf("\nbyte_arr[%d] after shifting %d = 0x%x", i, num_bits_to_shift, byte_arr[i]);
      if (i < arr_size -1)
      {
        byte_arr[i+1] |= (carry <<(8-num_bits_to_shift)); 
      }
      printf("\nbyte_arr[%d] after | with carry = 0x%x", i, byte_arr[i]);
      //carry = byte_arr[i] & mask;
      printf("\ncarry=%d", carry);
//      carry = byte_arr[i]<<(8-num_bits_to_shift);
//      byte_arr[i] >>= num_bits_to_shift;
    }

  }
}
*/
/** Shift an array right.
 * @param ar The array to shift.
 * @param size The number of array elements.
 * @param shift The number of bits to shift.
 */
void shift_right(unsigned char *ar, int size, int shift)
{
    int carry = 0;                              // Clear the initial carry bit.
    while (shift--) {                           // For each bit to shift ...
        for (int i = size - 1; i >= 0; --i) {   // For each element of the array from high to low ...
            int next = (ar[i] & 1) ? 0x80 : 0;  // ... if the low bit is set, set the carry bit.
            ar[i] = carry | (ar[i] >> 1);       // Shift the element one bit left and addthe old carry.
            carry = next;                       // Remember the old carry for next time.
        }   
    }
}  

int main()
{
  BYTE byte_arr[] = {0x07, 0x01};
  shift_right(byte_arr, 2, 2);
  printf("Result - 0x%x 0x%x", byte_arr[0], byte_arr[1]);
  return 0;
}

