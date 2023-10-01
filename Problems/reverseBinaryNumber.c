/* Reverse a binary number */

#include <stdio.h>

unsigned int reverseBits(unsigned int num)
{
  unsigned int rev = 0;
  while (num)
  {
    rev = rev<<1;
    rev |= num&1;
    num = num>>1;
  }
  return rev;

}

int main()
{
  unsigned int num = 11;
  unsigned int reverse = reverseBits(num);
  printf("Reverse of %u is %u", num, reverse);

  return 0;
}
