/*
Leetcode E 190 Reverse Bits

Best Approach 1 - Compare 0th and 31st, 1st and 30th and if they are same dont do anything, flip individual bits if they are different
Approach 2 - Brute force - get every bit and set it at 32-i position in the result.
Approach 3 - Incorrect due to trailing zeros
Good Approach 4 - Without loops. Reverse in batches of 16, 8, 4, 2, 1 = Results in reverse of entire uint32.

Example 1:

Input: n = 00000010100101000001111010011100
Output:    964176192 (00111001011110000010100101000000)
Explanation: The input binary string 00000010100101000001111010011100 represents the unsigned integer 43261596, so return 964176192 which its binary representation is 00111001011110000010100101000000.

Output:
Reverse=964176192
Reverse=964176192
Reverse=30130506 (Incorrect)
Reverse=964176192
*/

#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"

uint32_t reverseBits(uint32_t n) {
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

/*
Solution 2 - Brute Force - Get every bit from the right say ith position and and set it to 32-i position in reversed and keep ORin it
IMP - For reversed, START SETTING FROM 32nd position to make sure trailing zeros in n won't cause problems. 
*/
uint32_t reverseBits0(uint32_t n) {

  uint8_t count = sizeof(n)*8;
  uint32_t reversed = 0;

  while(n)
  {
    reversed |= (n&1)<<(count-1);
    n = n>>1;
    count--;
  }
  return reversed;
}


/* Solution 3 - won't work because of leading and trailing zeros will end the loop before !!!!*/
/* @TODO-INCORRECT ANSWER */
uint32_t reverseBits1(uint32_t n)
{
  uint32_t reverse = 0;
  while(n)
  {
    reverse |= (n & 0x1);
    reverse = reverse<<1;
    n = n>>1;
  }
  return reverse;
}


/* Solution 4 - copied from Leetcode editorial
No need of any loops
*/
uint32_t reverseBits2(uint32_t n) {
        n = (n >> 16) | (n << 16);
        n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
        n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
        n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
        n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
        return n;
}

int main()
{
  uint32_t num = 43261596;
  printf("\nReverse=%d", reverseBits(num));
  printf("\nReverse=%d", reverseBits0(num));
  printf("\nReverse=%d", reverseBits1(num));
  printf("\nReverse=%d", reverseBits2(num));
  return 0;
}
