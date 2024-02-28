#include <stdio.h>
#include <stdint.h>
int main()
{
  uint16_t num = 0x1234;
  uint16_t result = 0;
  uint16_t odd_bits = num & 0xAAAA;
  uint16_t even_bits = num & 0x5555;

  //Right shift odd bits
  odd_bits >>= 1;

  //Left shift even bits
  even_bits <<= 1;

  result = (even_bits|odd_bits);
  printf("\n 0x%x after swapping individual bits 0x%x", num, result);

  return 0;
}
  
