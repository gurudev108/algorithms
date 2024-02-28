/*
This problem was asked by Google.

Given a string of parentheses, write a function to compute the minimum number of parentheses
to be removed to make the string valid (i.e. each open parenthesis is eventually closed).

For example, given the string "()())()", you should return 1. Given the string ")(", you 
should return 2, since we must remove all of them.
*/

#include <stdio.h>

int minRemoveToMakeValid(char *s) {
    int openCount = 0;  // Count of open parentheses
    int removeCount = 0;  // Count of parentheses to be removed

    // First pass: Remove excess closing parentheses
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] == '(') {
            openCount++;
        } else if (s[i] == ')') {
            if (openCount > 0) {
                openCount--;  // Matched a closing parenthesis with an open one
            } else {
                removeCount++;  // Excess closing parenthesis, need to remove
            }
        }
    }

    // Second pass: Remove excess open parentheses
    openCount = 0;  // Reset openCount
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] == '(') {
            if (removeCount > 0) {
                removeCount--;  // Remove excess open parenthesis
            } else {
                putchar(s[i]);  // Output valid open parenthesis
            }
            openCount++;
        } else if (s[i] == ')') {
            putchar(s[i]);  // Output valid closing parenthesis
            openCount--;
        } else {
            putchar(s[i]);  // Output other characters
        }
    }

    return removeCount;
}

int main() {
    char inputString[100];

    // Input value
    printf("Enter a string of parentheses: ");
    scanf("%s", inputString);

    // Output the modified string and get the minimum removal count
    int removalCount = minRemoveToMakeValid(inputString);
    printf("\nMinimum number of parentheses to be removed: %d\n", removalCount);

    return 0;
}

