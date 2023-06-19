/* This file contains my experiments with bitwise operations in embedded C */

#include <stdio.h>  /* printf */
#include <stdint.h> /* uint8_t */

uint8_t countBitsSet(uint32_t num) 
{
  uint8_t count = 0;
  uint32_t mask = 0x1;
  while (num)
  {
    if (num & mask)
      count++;
    num >>= 1;
  }
  return count;
}

void bitwise_main(void)
{
  uint8_t count=0;
  uint32_t input = 11;
  printf("\n===Bitwise===\n");
  count = countBitsSet(input);
  printf("countBitsSet(%d) = %d\n", input, count);
  return;
}

int main()
{
  bitwise_main();
  return 0;
}


