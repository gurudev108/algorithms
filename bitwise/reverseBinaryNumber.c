/* Reverse a binary number */

#include <stdio.h>

unsigned int reverseBits0(unsigned int num)
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

//Approach 2 - combine first 2 lines into 1
unsigned int reverseBinary(unsigned int num) {
    unsigned int result = 0;

    while (num > 0) {
        // Shift the result to the left and add the last bit of num to it
        result = (result << 1) | (num & 1);
        // Right shift num to remove the last bit
        num = num >> 1;
    }

    return result;
}

uint32_t reverseBits1(uint32_t n) {
    n = (n >> 16) | (n << 16);
    n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
    n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
    n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
    n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
    return n;
}

uint32_t reverseBits2(uint32_t n) {

  uint8_t count = sizeof(n)*8;
  uint32_t reversed = 0;

  while(n)
  {
    reversed |= (n&1)<<count-1;
    n = n>>1;
    count--;
  }
  return reversed;
}

uint32_t reverseBits3(uint32_t n) {

  uint8_t count = sizeof(n)*8;
  uint8_t pos1 = 0, pos2 = 0;
  for (int i=0; i<count/2; i++)
  {
    pos1 = i;
    pos2 = count-i-1;
    if ((n>>pos1 & 1) != (n>>pos2 & 1))
    {
      printf("\n Flip bit i:%d and 32-i-1:%d :: %d %d is unequal", 
        pos1, pos2, (n>>pos1 & 1), (n>>pos2 & 1));
      n = n ^ ((uint32_t)1<<pos1);
      n = n ^ ((uint32_t)1<<pos2);
    }
    else
    {
      printf("\n i:%d and 32-i-1:%d :: %d %d is equal", 
        pos1, pos2, (n>>pos1 & 1), (n>>pos2 & 1));
    }
  }
  return n;
}

int main()
{
  unsigned int num = 11;
  unsigned int reverse = reverseBits(num);
  printf("Reverse of %u is %u", num, reverseBits(num));
  printf("Reverse of %u is %u", num, reverseBits(num));

  return 0;
}
