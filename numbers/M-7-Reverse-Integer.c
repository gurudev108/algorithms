/*
Leetcode M 7. Reverse Integer with Overflow/Underflow 

Given a signed 32-bit integer x, return x with its digits reversed. If reversing x causes the value to go outside the signed 32-bit integer range [-231, 231 - 1], then return 0.

Assume the environment does not allow you to store 64-bit integers (signed or unsigned).

Example 1:

Input: x = 123
Output: 321

Output:
Enter an integer: 120
Reversed integer: 21

Enter an integer: -123
Reversed integer: -321
*/
#include <stdio.h>
#include <limits.h>

int reverse(int x) {
    int reversed = 0;

    while (x != 0) {
        int digit = x % 10;
        x /= 10;

        // Check for overflow/underflow before updating reversed
        // if (reversed > INT_MAX / 10 || (reversed == INT_MAX / 10 && digit > 7)) {
        if (reversed > INT_MAX / 10) {
            return 0; // Overflow condition
        }
        //if (reversed < INT_MIN / 10 || (reversed == INT_MIN / 10 && digit < -8)) {
        if (reversed < INT_MIN / 10) {
            return 0; // Underflow condition
        }

        reversed = reversed * 10 + digit;
    }

    return reversed;
}

int main() {
    int x;

    // Example usage:
    printf("Enter an integer: ");
    scanf("%d", &x);

    int result = reverse(x);
    printf("Reversed integer: %d\n", result);

    return 0;
}

