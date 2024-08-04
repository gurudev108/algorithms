/* If we have to rotate 3 bits from LSB to MSB, we can 
right shift by 3 and | it with left shift by 5(8-3) */ 
#include <stdio.h>
#include <stdint.h>

uint16_t rotate_right(uint16_t value, int count) {
    int n = sizeof(value) * 8; // bit size of the data type
    return (value << (n-count)) | (value >> (count));
}

uint16_t rotate_left(uint16_t value, int count) {
    int n = sizeof(value) * 8; // bit size of the data type
    return (value << count) | (value >> (n-count));
}

int main()
{
  uint16_t num = 0x1007;
  uint16_t num2 = 0xb001;
  printf("\n%x rotated 3 bits to right = %x",num, rotate_right(num, 3));
  printf("\n%x rotated 3 bits to left = %x",num, rotate_left(num2, 3));

  return 0;
}
