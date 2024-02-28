/*
209. Minimum Size Subarray Sum
Medium
Given an array of positive integers nums and a positive integer target, return the minimal length of a
subarray whose sum is greater than or equal to target. If there is no such subarray, return 0 instead.
*/

#include <stdio.h>

int minSubArrayLen(int target, int* nums, int numsSize) {
    int minLength = numsSize + 1; // Initialize the minimum length to a value greater than numsSize
    int sum = 0; // Initialize the sum of the current window
    int start = 0; // Start index of the current window

    for (int end = 0; end < numsSize; ++end) {
        // Expand the window by including the current element
        sum += nums[end];
        // ##IMP
        // Shrink the window as long as the sum is greater than or equal to the target
        while (sum >= target) {
            // Update the minimum length
            if (end - start + 1 < minLength) {
                minLength = end - start + 1;
            }

            // Shrink the window by excluding the leftmost element
            sum -= nums[start];
            ++start;
         printf("\n While Debug start %d end %d minLength %d sum %d", start, end, minLength, sum);
        }
     
         printf("\n For Debug start %d end %d minLength %d sum %d", start, end, minLength, sum);
    }

    // If minLength is still greater than numsSize, no valid subarray was found
    return (minLength > numsSize) ? 0 : minLength;
}

// Main function for testing
int main() {
    int target = 7;
    int nums[] = {2, 3, 1, 2, 4, 3};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int result = minSubArrayLen(target, nums, numsSize);

    printf("Input: target = %d, nums = {", target);
    for (int i = 0; i < numsSize; ++i) {
        printf("%d", nums[i]);
        if (i < numsSize - 1) {
            printf(", ");
        }
    }
    printf("}\n");

    printf("Output: %d\n", result);

    return 0;
}


