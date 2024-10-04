/*Good morning! Here's your coding interview problem for today.

This problem was asked by Apple.

Gray code is a binary code where each successive value differ in only one bit, as well as when wrapping around. Gray code is common in hardware so that we don't see temporary spurious values during transitions.

Given a number of bits n, generate a possible gray code for it.

For example, for n = 2, one gray code would be [00, 01, 11, 10].

Approach:
Gray Code = i ^ (i>>1);
Print binary representation 

Verified Output:
n = 3,
000
001
011
010
110
111
101
100
*/

#include <stdint.h>
#include <stdio.h>

void generateGrayCode(uint8_t n)
{
  /* Efficiently compute pow(2,n) */
  uint16_t numCode = 1<<n;

  for (uint16_t i = 0; i<numCode; i++)
  {
    /* Formula for gray code */
    uint16_t gray = i ^ (i>>1);

    /* Print binary representation of gray code */
    for (int8_t j = n-1; j>=0; j--)
    {
      putchar((gray&(1<<j))?'1':'0');
    }
    putchar('\n');
  }
}

int main()
{
  uint8_t n = 3;
  generateGrayCode(n);
  return 0;
}
