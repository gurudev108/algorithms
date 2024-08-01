/* 
Leetcode M 55. Jump Game

You are given an integer array nums. You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position.

Return true if you can reach the last index, or false otherwise

Approach:
Greedy - The greedy approach focuses on making the optimal choice at each step to ensure that the overall solution is optimal. In this case, the algorithm tries to maximize the reachable index (maxReach) at each step. It does this by iterating through the array and updating the farthest index that can be reached (maxReach). As soon as maxReach reaches or exceeds the last index, the function returns true. If at any point the current index exceeds maxReach, it means that we cannot proceed further, and the function returns false.

Output:
True

Verified on Leetcode 88-16
*/
#include <stdio.h>
#include <stdbool.h>

bool canJump(int* nums, int numsSize) {
    int maxReach = 0; // Maximum index we can reach
    
    for (int i = 0; i < numsSize; i++) {
        if (i > maxReach) {
            // If the current index is beyond the maximum reachable index, we can't proceed
            return false;
        }
        // Update the maximum reachable index
        if (i + nums[i] > maxReach) {
            maxReach = i + nums[i];
        }
        // If we can reach or exceed the last index, return true
        if (maxReach >= numsSize - 1) {
            return true;
        }
    }
    
    return false;
}

int main() {
    int nums[] = {2, 3, 1, 1, 4}; // Example input
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    if (canJump(nums, numsSize)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}

