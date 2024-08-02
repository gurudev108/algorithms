/*
Leetcode M 371 Sum of Two Integers

Given two integers a and b, return the sum of the two integers without using the operators + and -.

Example 1:

Input: a = 1, b = 2
Output: 3

Approach:
To solve the problem of summing two integers without using the + and - operators, you can use bitwise operations. Specifically, you can leverage the bitwise XOR (^) and AND (&) operators to perform the addition.

Here’s how you can implement this in C:

Bitwise XOR (^): This operation performs addition without carrying. It adds bits where there is no carry.
Bitwise AND (&): This operation helps to compute the carry. The carry is shifted left by one bit using the bitwise left shift (<<) operation.
The idea is to repeatedly apply these operations until there are no more carries.


Verified Output:
Enter two integers: 2
3
Sum of 2 and 3 is: 5

Enter two integers: 9
2
Sum of 9 and 2 is: 11
*/

#include <stdio.h>

// Function to add two integers without using '+' or '-' operators
int getSum(int a, int b) {
    // Loop until there is no carry
    while (b != 0) {
        // Calculate carry bits
        int carry = a & b;

        // Calculate sum without carry
        a = a ^ b;

        // Shift carry bits to the left and add to a
        b = carry << 1;
    }

    return a;
}

int main() {
    int a, b;

    // Example usage:
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);

    int result = getSum(a, b);
    printf("Sum of %d and %d is: %d\n", a, b, result);

    return 0;
}

