/* This file contains my experiments with bitwise operations in embedded C */

#include <stdio.h>  /* printf */
#include <stdint.h> /* uint8_t */
#include <limits.h> 

/* NOTES

CHAR_BIT could be defined as a MACRO with value 8, its also defined in limits.h. 
 When the compiler sees the expression sizeof(int) * CHAR_BIT, it will substitute the value of
 CHAR_BIT that is defined in the system header files.

^ is used for XOR, and not exponentiation
 FLip all the bits - XOR with 0xFFFFFFFF

x & (-x) = Get the rightmost 1-bit and set all the other bits to 0
 x = 7        0 0 0 0 0 1 1 1 
 -7 = ~x+1    1 1 1 1 1 0 0 1 // rightmost 1-bit is common between 7 and -7
 Hence, x and -x have just one bit in common - the rightmost 1-bit. 

x & (x-1) = turn off the rightmost bit, used to check POWER of 2
 
 */

uint32_t setBit(uint32_t num, uint8_t position)
{
  uint8_t mask = 1<<position;
  return num | mask;
}

uint32_t clearBit(uint32_t num, uint8_t position)
{
  uint8_t mask = 1<<position;
  return num & ~mask;
}

/* Number of bits set, also known as HAMMING WEIGHT
POWER of 2 = if only 1 bit is set
Loop through the bits using right shift until num is 0 and each time comparing it with mask 0x1 
Below function uses mask and a if check but you can get rid of them by count += num & 1; */
/* UNOPTIMIZED - checks every bit */
uint8_t countBitsSet(uint32_t num) 
{
  uint8_t count = 0;
  uint8_t mask = 0x1;
  while (num)
  {
    if (num & mask) // count += num & 1;
      count++;
    num >>= 1;
  }
  return count;
}

/* Optimization of countBitsSet using Brian Kernighan's algorithm of n & (n-1) where it sets
the rightmost set bit to 0. If the number had just 1 bit set then n&(n-1) will be 0.*/
uint8_t countBitsSet_1(uint32_t num)
{
  uint8_t count = 0;
  while(num)
  {
    num &= (num - 1);
    count++;
  }
  return count;
}

uint32_t highestPowerof2(uint32_t n)
{
    int res = 0;
    for (int i = n; i >= 1; i--) {
        // If i is a power of 2
        if ((i & (i - 1)) == 0) { 
        // means only 1 bit was set hence the expression set that rightmost set bit to 0
            res = i;
            break;
        }
    }
    return res;
}

/* LEETCODE 461 HAMMING DISTANCE
The Hamming distance between two integers is the number of positions at which the corresponding bits are different.
Hamming distance is an interesting metric that is widely applied in several domains, e.g. in coding theory for
error detection, in information theory for quantifying the difference between strings.
*/
int hammingDistance(int x, int y){
  int count = 0;
  /* after XOR we convert the hamming distance problem into bit counting */
  int xor = x^y;
  while (xor)
  {
      xor &= (xor-1);
      count++;
  }
  return count;
}

uint8_t get_sign(uint32_t num)
{
  /* Method 1 - Right shift to fetch MSB which is the sign */
  return (num >> ((sizeof(int) * CHAR_BIT) - 1));  

  /* Method 2 - XOR with 1 */
  //num ^ 1

}

// Find the number of trailing zeros in an integer
uint32_t trailing_zeros(uint32_t num) {
  int count = 0;
  while ((num & 1) == 0) {
    count++;
    num >>= 1;
  }
  return count;
}

/* ROTATE BITS - Circular shift
Whatever is lost in the shift is moved to the other side */
uint32_t circular_shift(uint32_t n, uint32_t d) {
  return (n >> d) | (n << (sizeof(int) * CHAR_BIT - d));
}

#if 0
void printPowerSet(char *set, int set_size)
{
    /*set_size of power set of a set with set_size
      n is (2**n -1)*/
    unsigned int pow_set_size = pow(2, set_size);
    int counter, j;
 
    /*Run from counter 000..0 to 111..1*/
    for(counter = 0; counter < pow_set_size; counter++)
    {
      for(j = 0; j < set_size; j++)
       {
          /* Check if jth bit in the counter is set
             If set then print jth element from set */
          if(counter & (1<<j))
            printf("%c", set[j]);
       }
       printf("\n");
    }
}
#endif

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

/* Reverse set bit in a given number, Test with a negative number */



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
  uint32_t negative_input = -11;
  printf("\n===Bitwise===\n");
  count = countBitsSet_1(input);
  printf("countBitsSet(%d) = %d\n", input, count);
  printf("get_sign(%d) = %d, get_sign(%d) = %d\n",input, get_sign(input), negative_input, get_sign(negative_input)); 
  printf("trailing_zeros(%d) = %d\n", 64, trailing_zeros(64));
  printf("Rotate bits of %x by %d = %x\n", 0xABCD1234, 16, circular_shift(0xABCD1234, 16));
  return;
}

int main()
{
  /* Check if the machine is Big Endian or Little Endian */
  check_endianess1();
  bitwise_main();
  return 0;
}


