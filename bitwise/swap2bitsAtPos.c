/*
Swap two bits at a given position in an integer
Input:
 
n = 31 (31 in binary is 00011111)
p = 2, q = 6 (3rd and 7th bit from the right)
 
Output: 91
 
Explanation: 91 in binary is 01011011
*/

#include <stdio.h>

// Approach 1
// Function to swap bits at position `p` and `q` in integer `n`
int swap(int n, int p, int q)
{
    // if bits are different at position `p` and `q`
    if (((n & (1 << p)) >> p) ^ ((n & (1 << q)) >> q))
    {
        /* swap bits at pos p and q */
        n ^= (1 << p);
        n ^= (1 << q);
    }
    return n;
}

// Approach 2 (RECOMMENDED - lesser shifts)
// Function to swap bits at position `p` and `q` in integer `n`
int swap1(int n, int p, int q)
{
    // if bits are different at position `p` and `q`
    if (((n >> p) & 0x1) ^ ((n >>q) & 0x1))
    {
        n ^= (1 << p);
        n ^= (1 << q);
    }
    return n;
}
 
int main()
{
    int n = 31;
    int p = 2, q = 6;    // swap 3rd and 7th bit from the right
 
    n = swap (n, p, q);
    printf("\n%d", n);

    n = 31;
    n = swap1 (n, p, q);
    printf("\n%d", n);

    return 0;
}
