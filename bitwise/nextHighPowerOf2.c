/*
Given a positive number n, find the next highest power of 2. If n itself is a power of 2, return n.

Approach 1

The idea is to unset the rightmost bit of n until only one bit is left, which will be the last set bit of the given number. To handle the case when n is the power of 2, initially decrement n by 1. Note that this operation will not impact output as we are only concerned about the last set bit of n.

*/
#include <stdio.h>
#include <math.h>
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
