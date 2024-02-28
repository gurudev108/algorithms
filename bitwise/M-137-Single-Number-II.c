/*
https://leetcode.com/problems/single-number-ii/description/
Difficulty {Medium}
Topics {Array, Bitwise}

Given an integer array nums where every element appears three times except for one, which appears exactly once. Find the single element and return it.

You must implement a solution with a linear runtime complexity and use only constant extra space.



Approach
1. Loop through all the 32 bits
2. Count number of bits set at every index
3. Sum of bits set modulus 3 will be the bit for loner
4. Do this for all 32 bits
*/

#include <stdio.h>

int singleNumber(int* nums, int numsSize) {
    int loner = 0;
    for (int i=0; i<32; i++)
    {
        int bit_sum = 0;
        for (int j=0; j<numsSize; j++)
        {
            bit_sum += (nums[j]>>i) & 1;
        }
        int loner_bit = bit_sum%3;
        loner |= loner_bit<<i;

    }
    return loner;
    
}
int main()
{
	int nums[] = {0,1,0,1,0,1,99};
	printf("Test");
	int result = singleNumber(nums, sizeof(nums)/sizeof(nums[0]));
	printf("Loner =%d", result);
	return 0;
}
