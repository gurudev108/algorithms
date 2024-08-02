/*
Find the missing number and duplicate elements in an array

Given an integer array of size n, with all its elements between 1 and n and one element occurring twice and one element missing.
Find the missing number and the duplicate element in linear time and without using any extra memory

Input:  arr[] = [4, 3, 6, 5, 2, 4]
 
Output: The duplicate and missing elements are 4 and 1, respectively


We can solve this problem in linear time and constant space using the XOR operator. We know that if we XOR a number with
itself an odd number of times, the result is a number itself; otherwise, if we XOR a number an even number of times with
itself, the result is 0. Also, XOR with 0 is always the number itself.

How to find x and y?

We know that any set bit in result = (x ^ y) will be either set in x or y (but not in both as a bit will only set in 
result when it is set in one number and unset in the other).

The idea is to consider the rightmost set bit in result (or any other set bit) and split the array/range into two lists:

The first list contains all the array elements and numbers in the range that have this bit set.
The second list contains all the array elements and numbers in the range that have this bit unset.
As the rightmost bit is set in one number and unset in the other, we will have a duplicate element present in one list
and a missing number present. Basically, we have isolated traits of one number with the other, so that both x and y 
will go to different lists.

Now iterate both lists once more and do XOR on each element. The result will be the duplicate element present in one 
list and the missing number present in the other list (since elements appearing twice will cancel each other).

Output:
Duplicate number: 2
Missing number: 5
*/


#include <stdio.h>

void findDuplicateAndMissing(int arr[], int n) {
    int xorResult = 0;
    for (int i = 0; i < n; i++) {
        xorResult ^= arr[i];
    }
    for (int i = 1; i <= n; i++) {
        xorResult ^= i;
    }

    // @TODO-IMP Get the rightmost set bit of xorResult
    int set_bit = xorResult & ~(xorResult - 1); // or xorResult & (-xorResult)

    int x = 0, y = 0; // x will hold the duplicate, y will hold the missing number
    // after running output was opposite, x was the missing number and y was the dup
    for (int i = 0; i < n; i++) {
        if (arr[i] & set_bit) {
            x ^= arr[i];
        } else {
            y ^= arr[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        if (i & set_bit) {
            x ^= i;
        } else {
            y ^= i;
        }
    }

    printf("Duplicate number: %d\n", y);
    printf("Missing number: %d\n", x);
}

int main() {
    int arr[] = {4, 3, 2, 7, 8, 2, 6, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    findDuplicateAndMissing(arr, n);

    return 0;
}

