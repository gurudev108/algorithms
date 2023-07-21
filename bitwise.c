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

void check_endianess (void)
{
  unsigned int value = 0x12345678;
  unsigned char *ptr = (unsigned char *)&value;

  if (*ptr == 0x12)
  {
    printf("Big Endian value=%d char*ptr=%d\n", value, *ptr);
  }
  else if (*ptr == 0x78)
  {
    printf("Little Endian *ptr=%x %x\n", *ptr, *(ptr+1));
  }
}

void check_endianess1 (void)
{
  int num = 1;
  if (*(char* )&num == 1)
    /* Little Endian saves 01 as 10 - saved in memory as 0000001 0000000 */
    printf("Little Endian");
  else
    /* Big Endian saves 01 as 01 - saved in memory as 0000000 00000001 */ 
    printf("Big Endian");
}

/* Leetcode 1356. Sort Integers by The Number of 1 Bits
You are given an integer array arr. Sort the integers in the array in ascending
order by the number of 1's in their binary representation and in case of two or
more integers have the same number of 1's you have to sort them in ascending
order. Return the array after sorting it.
Constraints 1<=arr.length<=500, 0<=arr[i]<=10^4 */


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
  /* Check if the machine is Big Endian or Little Endian */
  check_endianess1();
  bitwise_main();
  return 0;
}


