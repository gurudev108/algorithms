/*
Leetcode 948. Bag of tokens
You start with an initial power of power, an initial score of 0, and a bag of tokens given as an integer array tokens, where each tokens[i] denotes the value of tokeni.

Your goal is to maximize the total score by strategically playing these tokens. In one move, you can play an unplayed token in one of the two ways (but not both for the same token):

Face-up: If your current power is at least tokens[i], you may play tokeni, losing tokens[i] power and gaining 1 score.
Face-down: If your current score is at least 1, you may play tokeni, gaining tokens[i] power and losing 1 score.
Return the maximum possible score you can achieve after playing any number of tokens.

Verified on Leetcode 45-6

Approach - Sort and Greedy, use 2 pointers

Example 1:
Input: tokens = [100], power = 50
Output: 0
Explanation: Since your score is 0 initially, you cannot play the token face-down. You also cannot play it face-up since your power (50) is less than tokens[0] (100).

Example 2:
Input: tokens = [200,100], power = 150
Output: 1
Explanation: Play token1 (100) face-up, reducing your power to 50 and increasing your score to 1.
There is no need to play token0, since you cannot play it face-up to add to your score. The maximum score achievable is 1.
Output:
Maximum Score: 2
*/

#include <stdio.h>
#include <stdlib.h>

// Compare function for qsort to sort tokens in ascending order
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int bagOfTokensScore(int* tokens, int tokensSize, int power) {
    // Sort tokens in ascending order
    qsort(tokens, tokensSize, sizeof(int), compare);
    
    int score = 0;
    int maxScore = 0;
    int left = 0;
    int right = tokensSize - 1;
    
    while (left <= right) {
        if (power >= tokens[left]) {
            // Play token face-up
            power -= tokens[left];
            score++;
            left++;
            if (score > maxScore) {
                maxScore = score;
            }
        } else if (score > 0) {
            // Play token face-down
            power += tokens[right];
            score--;
            right--;
        } else {
            break;
        }
    }
    
    return maxScore;
}

int main() {
    int tokens[] = {100, 200, 300, 400};
    int power = 200;
    int tokensSize = sizeof(tokens) / sizeof(tokens[0]);
    
    int result = bagOfTokensScore(tokens, tokensSize, power);
    printf("Maximum Score: %d\n", result); // Output: 2
    
    return 0;
}

