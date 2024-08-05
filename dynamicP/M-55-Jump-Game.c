/*
Leetcode M 55. The Jump Game
Also see Greedy

Approach: Trying DL just to understand it in comparison to Greedy
A dynamic programming (DP) approach would involve breaking down the problem into smaller subproblems and solving each one, typically storing the results of these subproblems to avoid redundant computations. For the "Jump Game" problem, a DP approach might involve creating an array dp where dp[i] represents whether the end can be reached starting from index i. However, this would typically involve checking all possible jumps from each position and is often more computationally expensive than the greedy approach.

Output:
True

Verified SLOW on Leetcode 7-9
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool canJump(int* nums, int numsSize) {
    // Create a dp array and initialize all elements to false
    bool* dp = (bool*)malloc(numsSize * sizeof(bool));
    for (int i = 0; i < numsSize; i++) {
        dp[i] = false;
    }
    
    // The last position is always reachable from itself
    dp[numsSize - 1] = true;

    // Fill the dp array from right to left
    for (int i = numsSize - 2; i >= 0; i--) {
        int furthestJump = i + nums[i];
        // Check if we can reach a position with dp[j] = true
        for (int j = i + 1; j <= furthestJump && j < numsSize; j++) {
            if (dp[j]) {
                dp[i] = true;
                break;
            }
        }
    }

    // The result for the first index
    bool result = dp[0];
    
    // Free allocated memory
    free(dp);

    return result;
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

/*
Explanation
Dynamic Programming Array (dp):
We create a boolean array dp of the same size as the input array nums. dp[i] will be true if the end of the array can be reached starting from index i; otherwise, it will be false.
Initialization:
We initialize dp[numsSize - 1] to true because the last position can always reach itself.
Filling the DP Array:
We iterate over the array from right to left (starting from the second-to-last index) and determine if the current index i can reach an index j such that dp[j] is true.
For each i, we calculate furthestJump, which is the farthest index we can jump to from i. Then, we check all indices j from i + 1 to furthestJump to see if any of them are reachable (i.e., dp[j] is true). If we find such a j, we set dp[i] to true and break out of the loop.
Result:
The final result is stored in dp[0], indicating whether the end of the array can be reached from the start.
Memory Management:
We allocate memory for the dp array dynamically and free it after use to prevent memory leaks.
This dynamic programming solution has a time complexity of O(n^2) and a space complexity of O(n), where n is the number of elements in the array. The quadratic time complexity arises because, for each element, we may potentially check all elements to the right.
*/
