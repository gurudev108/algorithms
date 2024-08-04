/*
Given a positive number n, find the next highest power of 2. If n itself is a power of 2, return n.

Approach 1
The idea is to manipulate the binary representation of the number so that all bits to the right of the 
most significant bit are set to 1, then add 1 to obtain the next power of 2.

Approach 2

The idea is to unset the rightmost bit of n until only one bit is left, which will be the last set 
bit of the given number. To handle the case when n is the power of 2, initially decrement n by 1. 
Note that this operation will not impact output as we are only concerned about the last set bit of n.

*/
#include <stdio.h>
#include <math.h>

// Function to find the next power of 2 greater than or equal to num
unsigned int findNextPowerOf2(unsigned int num) {
    // Special case when num is 0
    if (num == 0) return 1;

    // Decrease num by 1 to handle the case where num is already a power of 2
    num--;

    /* Set all bits to the right of the most significant bit
    The sequence of OR operations with right-shifted versions of num progressively sets all bits to the right of the most significant bit.
    num |= num >> 1; sets the rightmost bit.
    num |= num >> 2; sets the next two bits.
    And so on, doubling the number of set bits with each operation. */
    num |= num >> 1; // use rightmost bit and >> shift and OR to have 1 propopated to 2 rightmost bit and so on.
    num |= num >> 2;
    num |= num >> 4;
    num |= num >> 8;
    num |= num >> 16;

    // Increment num to get the next power of 2
    return num + 1;
}

//Approach 2
unsigned int findNextPowerOf2(unsigned int n)
{
  n = n - 1;  // Decrement n to handle the case when n itself is a power of 2
  while (n &n-1)
  {
    n = n & (n-1);
  }
  // return next high power of 2
  return n<<1;
}

/* Approach 2 */
// Compute power of two greater than or equal to `n`
unsigned findNextPowerOf2_2(unsigned n)
{
    // decrement `n` (to handle the case when `n` itself
    // is a power of 2)
    n = n - 1;
 
    // initialize result by 2
    int k = 2;
 
    // double `k` and divide `n` in half till it becomes 0
    while (n >>= 1) {
        k = k << 1;    // double `k`
    }
 
    return k;
}

/* 
Approach 3 - Use log2()

The idea is to calculate position p of the last set bit of n and return a number with its p+1 bit set 
*/
// Compute power of two greater than or equal to `n`
unsigned findNextPowerOf2_3(unsigned n)
{
    // decrement `n` (to handle the case when `n` itself
    // is a power of 2)
    n = n - 1;
 
    // calculate the position of the last set bit of `n`
    int lg = log2(n);
 
    // next power of two will have a bit set at position `lg+1`.
    return 1U << (lg + 1);
}

int main()
{
  unsigned int num = 127;
  printf("\nApporach 1 Next power of 2 for %d is %d", num, findNextPowerOf2(num));
  printf("\nApproach 2 Next power of 2 for %d is %d", num, findNextPowerOf2_2(num));
  printf("\nApproach 3 Next power of 2 for %d is %d", num, findNextPowerOf2_3(num));
  return 0;
} 
